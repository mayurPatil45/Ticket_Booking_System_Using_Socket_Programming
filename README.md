# Ticket_Booking_System_Using_Socket_Programming

### OVERVIEW: 
In our day to day lives we go around many places and at least once we might have come around booking tickets, may it be for movies or travel. This project provides a scaled-down example of how tickets might be ordered in various fields.

### IMPLEMENTATION: 
This project uses a single source file called "seats," which provides information about the seats' availability. In this assignment, we will use the illustration of a movie theatre with 25 seats, five rows, and five seats per row. The numerals 0 and 1 make up the entire number 25 in this text file. The spots marked with a 0 indicate that the corresponding seat is unoccupied and available for reservation. The ones with 1s indicate that they are filled.

Two files, one for the server and one for the client, were required for socket programming. A TCP connection was employed since we needed 2-way communication, hence a TCP connection and data stream were used. Creating the socket, binding the address, listening, and accepting the connection are all done on the server side, according to the usual procedure, generating the socket and connecting to the server on the client side

The port number must be specified in the server file using multiple arguments. Even while we could specify a port and save it inside the program, we instead asked the user for it in case, upon restart, the software just aborts without indicating that the port is already in use. Instead, we can be in charge and run the code on a different port number. When launching a client file, there are two inputs available as arguments. The first is the IP address, which is 127.0.0.1 because it is being used by other terminals on the same system. Obviously, the second one is the port number, which needs to match that on the server.

When the client connects to the server, the server first opens the Seats.txt file and saves the data in an array. Here the iterator iterates over the data and counts the number of zeros or the total number of digits available. Now that the data is ready, the server sends a message to the client asking for the sheet the client needs. If the client requests more seats than the total number of seats available, the server rejects the request, sends back a message, and closes the connection. On the other hand, if the seat requested by the customer is within the available range, the server will send a message with seat occupancy instructions and display the seat matrix. 

The user can view this matrix and select a seat. Now, if the place is occupied, the server receives the information, calculates the position in the array based on this data, and compares it with the previous data. If there are seats available, the message "Ticket x reserved" will be displayed. x is the ticket number. If the seat is not available (i.e. the user has selected a seat by mistake), in this case, the server will issue a warning and close the ticket. Still, in this case, the server will discard the recorded data and replace the original data is not changed. After tickets are booked, write a file with the updated array. So the data will be updated.

When the program is restarted or used by another customer, the previously booked ticket will be displayed and the new user cannot select it. This is the point of ticket reservation. So the program ran successfully.

### ⭐ Algorithm

STEP 1: START

STEP 2: Establish secure connection between client sever(Enter proper ip address)

STEP 3: Fix errors(if any) while establishing connection.

STEP 4: After establishing connection ask (user)client side to enter the choice.

STEP 5: On client side, check if the choice is valid or not.
If(not valid)
ask user to enter a valid choice
Else
Send choice to server 

STEP 6: Server Side Recieve the choice sent by client.

STEP 7: Load the contents of file associated with the choice into buffer and send it to client side.

STEP 8: The result is displayed on the client side to the user (as soon as buffer arrives on the client side).

STEP 9: END


### 👏 And it's done!
