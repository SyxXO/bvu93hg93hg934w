void gateOpener(){

	int port = 1024;

	char[] ipAddress;
	strcopy(ipAddress, "get.ip").c_str());	// Makes an Array.

	char[24] sendMessage;
	strcopy(sendMessage, "Please".c_string()); // Requests access to server

	connect_to_server(ipAddress, port);  //Connects to server
	send_to_server(sendMessage);

	char[] response;
	recieve_from_server(response);	// Servers response

	send_to_server(response); // Let me in

	startNextQuadrant();

}
