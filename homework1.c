#include "homework1.h"

void* client_echo(void* arg)
{
	int client_desc = *(int*)arg;
	char buffer[1024];
	in valread;

	while ((valread = read(client_desc, buffer, 1024)) > 0)
	{
		buffer[valread] = '\0';
		printf("Recieved %s", buffer);
		send(client_desc, buffer, valread, 0);
	}

	if (valread == 0)
	{
		printf("Client disconnected\n");
	}
	else if ( valread < 0 )
	{
		printf("Recieve failed\n");
	}

	close(client_desc);
	free(arg);
	return NULL;
}

int main(void)
{
	int socket_desc, * new_client_desc;
	struct sockaddr_in server_addr;
	int server_struct_length = sizeof(server_addr);

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_desc < 0)
	{
		printf("Error while creating the socket\n");
		return -1;
	}

	printf("Socket created successfully!\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("172.31.29.81");
	server_addr.sin_port = htons(8888);

	if (bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Could not bind to port\n");
		return -1;
	}

	printf("Successfully binded to port!\n");

	if (listen(socket_desc, 5) < 0)
	{
		printf("Server listening failed\n");
		return -1;
	}

	printf("Echo server is listening on port 8888\n");

	while (1)
	{
		new_client_desc = malloc(sizeof(int));
		if ((*new_client_desc = accept(socket_desc, (struct sockaddr*)&server_addr, &server_struct_length)) < 0)
		{
			printf("Accept failed\n");
			free(new_client_desc);
			continue;
		}

		printf("New connection accepted\n");

		pthread_t thread_id;
		if (pthread_create(&thread_id, NULL, client_echo, new_client_desc) != 0)
		{
			printf("pthread creation failed\n");
			close(*new_client_desc);
			free(new_client_desc);
		}

		pthread_detach(thread_id);
	}

	close(socket_desc);
	return 0;

}