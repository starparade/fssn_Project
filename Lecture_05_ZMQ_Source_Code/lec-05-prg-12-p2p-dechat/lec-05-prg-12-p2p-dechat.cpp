#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <sstream>
#include <Windows.h>
#include <IPTypes.h>
#include <iphlpapi.h>
#include <vector>
#include <cstring>

#include <zmq.hpp>

using namespace std;

vector<string>
split(string source)
{
	istringstream iss(source);
	string temp_str;
	vector<string> vector_s;
	vector_s.clear();

	if (source == "") {
		vector_s.push_back("");
		return vector_s;
	}

	while (getline(iss, temp_str, ':')) {
		vector_s.push_back(temp_str);
	}

	return vector_s;
}

string
search_nameserver(string ip_mask, string local_ip_addr, int port_nameserver)
{
	// Search for P2P name server in the local network.
	zmq::context_t context_search(1);
	zmq::socket_t req(context_search, zmq::socket_type::sub);
	for (int last = 1; last <= 255; last++) {
		string target_ip_addr = "tcp://" + ip_mask + "." + to_string(last) + ":" + to_string(port_nameserver);
		if (target_ip_addr.compare(local_ip_addr + ":" + to_string(port_nameserver)) != 0 || 
			target_ip_addr.compare(local_ip_addr + ":" + to_string(port_nameserver)) == 0) {
			req.connect(target_ip_addr);
		}
		req.set(zmq::sockopt::rcvtimeo, 2000);
		req.set(zmq::sockopt::subscribe, "NAMESERVER");
	}
	try {
		zmq::message_t res;
		req.recv(res, zmq::recv_flags::none);
		vector<string> res_list = split(res.to_string());
		if (res_list[0] == "NAMESERVER") {
			return res_list[1];
		}
		else {
			return "";
		}
	}
	catch (exception& e) { return ""; }
}

void
beacon_nameserver(string local_ip_addr, int port_nameserver)
{
	// Generate periodic (1 second) beacon message.
	zmq::context_t context_beacon(1);
	zmq::socket_t socket(context_beacon, zmq::socket_type::pub);
	string temp_addr_beacon = "tcp://" + local_ip_addr + ":" + to_string(port_nameserver);
	socket.bind(temp_addr_beacon);
	cout << "local p2p name server bind to tcp://"<< local_ip_addr << ":" << port_nameserver << "." << endl;
	
	while (true) {
		try {
			Sleep(1000);
			zmq::message_t msg(26);
			snprintf((char*)msg.data(), 26, "NAMESERVER:%s", local_ip_addr.c_str());
			socket.send(msg, zmq::send_flags::none);
		}
		catch (exception& e) {
			break;
		}
	}
}

void
user_manager_nameserver(string local_ip_addr, int port_subscribe)
{
	// User subscription manager {ip address and user id}.

	vector<vector<string>> user_db;
	user_db.clear();
	zmq::context_t context_user(1);
	zmq::socket_t socket(context_user, zmq::socket_type::rep);
	string temp_addr_user = "tcp://" + local_ip_addr + ":" + to_string(port_subscribe);
	socket.bind(temp_addr_user);
	cout << "local p2p db server activated at tcp://" 
		<< local_ip_addr << ":" << port_subscribe << "." << endl;
	
	while (true) {
		try {
			zmq::message_t message_user;
			socket.recv(message_user, zmq::recv_flags::none);
			vector<string> user_req = split(message_user.to_string());
			user_db.push_back(user_req);
			cout << "user registration '" << user_req[1] << "' from '" << user_req[0] << "'." << endl;
			zmq::message_t temp_message_user(3);
			snprintf((char*)temp_message_user.data(), 3, "%s", "ok");
			socket.send(temp_message_user, zmq::send_flags::none);
		}
		catch (exception& e) {
			break;
		}
	}
}

void
relay_server_nameserver(string local_ip_addr, int port_chat_publisher, int port_chat_collector, int user_name_len)
{
	// Relay message between p2p users.
	zmq::context_t context_relay(1);
	zmq::socket_t publisher(context_relay, zmq::socket_type::pub);
	string temp_addr_relay = "tcp://" + local_ip_addr + ":" + to_string(port_chat_publisher);
	publisher.bind(temp_addr_relay);
	zmq::socket_t collector(context_relay, zmq::socket_type::pull);
	temp_addr_relay = "tcp://" + local_ip_addr + ":" + to_string(port_chat_collector);
	collector.bind(temp_addr_relay);
	cout << "local p2p relay server activated at tcp://" << local_ip_addr << ":" 
		<< port_chat_publisher << " & " << port_chat_collector << "." << endl;

	while (true) {
		try {
			zmq::message_t message_relay;
			collector.recv(message_relay, zmq::recv_flags::none);
			cout << "p2p-relay:<==>" << message_relay.to_string() << endl;
			int strSize = 36 + user_name_len - 8;
			zmq::message_t temp_message_relay(strSize);
			snprintf((char*)temp_message_relay.data(), strSize, "RELAY:%s", message_relay.to_string().c_str());
			publisher.send(temp_message_relay, zmq::send_flags::none);
		}
		catch (exception& e) {
			break;
		}
	}
}

string
get_local_ip()
{
	string ip_addr;

	IP_ADAPTER_INFO* pAdapterInfo;
	ULONG            ulOutBufLen;
	DWORD            dwRetVal;
	pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) {
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}
	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) {
		printf("GetAdaptersInfo call failed with %d\n", dwRetVal);
	}
	PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
	while (pAdapter) {
		if (pAdapter->IpAddressList.IpAddress.String[0] != '0') {
			ip_addr = pAdapter->IpAddressList.IpAddress.String;
		}

		pAdapter = pAdapter->Next;
	}
	if (pAdapterInfo)
		free(pAdapterInfo);

	return ip_addr;
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		cout << "usage is 'python dechat.py _user-name_'." << endl;
		exit(1);
	}
	else {
		cout << "starting p2p chatting program." << endl;
	}

	string ip_addr_p2p_server = "";
	int port_nameserver = 9001;
	int port_chat_publisher = 9002;
	int port_chat_collector = 9003;
	int port_subscribe = 9004;

	string user_name = argv[1];
	string ip_addr = get_local_ip();
	string temp_ip_addr = ip_addr;
	for (string::iterator i = temp_ip_addr.begin(); i != temp_ip_addr.end(); ++i)
	{
		if (*i == '.') {
			*i = ' ';
		}
	}
	string ip_mask1, ip_mask2, ip_mask3, ip_mask4, ip_mask;
	istringstream iss(temp_ip_addr);
	iss >> ip_mask1 >> ip_mask2 >> ip_mask3 >> ip_mask4;
	ip_mask = ip_mask1 + '.' + ip_mask2 + '.' + ip_mask3;
	cout << "searching for p2p server." <<  endl;

	string name_server_ip_addr = search_nameserver(ip_mask, ip_addr, port_nameserver);
	if (name_server_ip_addr == "") {
		string ip_addr_p2p_server = ip_addr;
		cout << "p2p server is not found, and p2p server mode is activated." << endl;
		thread beacon_thread1 = thread(beacon_nameserver, ip_addr, port_nameserver);
		beacon_thread1.detach();
		cout << "p2p beacon server is activated." << endl;
		thread beacon_thread2 = thread(user_manager_nameserver, ip_addr, port_subscribe);
		beacon_thread2.detach();
		cout << "p2p subsciber database server is activated." << endl;
		thread beacon_thread3 = thread(relay_server_nameserver, ip_addr, port_chat_publisher, port_chat_collector, user_name.length());
		beacon_thread3.detach();
		cout << "p2p message relay server is activated." << endl;
	}
	else {
		string ip_addr_p2p_server = name_server_ip_addr;
		cout << "p2p server found at " << ip_addr_p2p_server 
			<< ", and p2p client mode is activated." << endl;
	}

	cout << "starting user registration procedure." << endl;

	zmq::context_t db_client_context(1);
	zmq::socket_t db_client_socket(db_client_context, zmq::socket_type::req);
	string temp_addr = "tcp://" + ip_addr_p2p_server + ":" + to_string(port_subscribe);
	db_client_socket.connect(temp_addr);
	int strSize = 24 + user_name.length() - 8;
	zmq::message_t msg1(strSize);
	temp_addr = ip_addr + ":" + user_name;
	snprintf((char*)msg1.data(), strSize, "%s", temp_addr.c_str());
	db_client_socket.send(msg1, zmq::send_flags::none);
	db_client_socket.recv(msg1, zmq::recv_flags::none);
	if (strcmp(msg1.to_string().c_str(), "ok") == 0) {
		cout << "user registration to p2p server completed." << endl;
	}
	else {
		cout << "user registration to p2p server failed." << endl;
	}

	cout << "starting message transfer procedure." << endl;

	zmq::context_t relay_client(1);
	zmq::socket_t p2p_rx(relay_client, zmq::socket_type::sub);
	p2p_rx.set(zmq::sockopt::subscribe, "RELAY");
	temp_addr = "tcp://" + ip_addr_p2p_server + ":" + to_string(port_chat_publisher);
	p2p_rx.connect(temp_addr);
	zmq::socket_t p2p_tx(relay_client, zmq::socket_type::push);
	temp_addr = "tcp://" + ip_addr_p2p_server + ":" + to_string(port_chat_collector);
	p2p_tx.connect(temp_addr);

	cout << "starting autonomous message transmit and receive scenario." << endl;

	while (true) {
		try {
			zmq::pollitem_t items[] = {
				{ p2p_rx, 0, ZMQ_POLLIN, 0 }
			};
			zmq::poll(items, 1, chrono::milliseconds(100));
			if (items[0].revents & ZMQ_POLLIN) {
				zmq::message_t msg2;
				p2p_rx.recv(msg2, zmq::recv_flags::none);
				vector<string> vector_s = split(msg2.to_string());
				cout << "p2p-recv::<<== " << vector_s[1] << ":" << vector_s[2] << endl;
			}
			else {
				srand((unsigned)time(NULL));
				int randNum = (rand() % 100) + 1;
				if (randNum < 10) {
					Sleep(3000);
					int strSize = 29 + user_name.length() - 8;
					zmq::message_t msg3(strSize);
					string temp_str = "(" + user_name + "," + ip_addr + ":ON)";
					snprintf((char*)msg3.data(), strSize, "%s", temp_str.c_str());
					p2p_tx.send(msg3, zmq::send_flags::none);
					cout << "p2p-send::==>> " << temp_str << endl;
				}
				else if (randNum > 90) {
					Sleep(3000);
					int strSize = 30 + user_name.length() - 8;
					zmq::message_t msg4(strSize);
					string temp_str = "(" + user_name + "," + ip_addr + ":OFF)";
					snprintf((char*)msg4.data(), strSize, "%s", temp_str.c_str());
					p2p_tx.send(msg4, zmq::send_flags::none);
					cout << "p2p-send::==>> " << temp_str << endl;
				}
			}
		}
		catch (exception& e) {
			break; 
		}
	}

	cout << "closing p2p chatting program." << endl;

    return 0;
}