/*
 * http-server.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <assert.h>  
#include <sys/wait.h>  
#include <sys/stat.h>


#define BUF_SIZE 4096

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

static void printUsage() {
    fprintf(stderr, "usage: http-server <server_port> <web_root> <mdb-lookup-host> <mdb-lookup-port>\n");
    fprintf(stderr, "   ex) http-server www.example.com 80 /index.html\n");
    exit(1);
}




int main(int argc, char **argv) {

    // Ignore SIGPIPE so that we don’t terminate when we call
    // send() on a disconnected socket
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        die("signal() failed"); 
    
    if (argc != 5) {
	printUsage();
    }

    // Assign server_port and web_root to correct command line arguments

    unsigned short serv_port = atoi(argv[1]);
    const char *web_root = argv[2];
    

    // Create a listening socket (also called server socket) 

    int servsock;
    if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");

    // Construct local address structure

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // any network interface
    servaddr.sin_port = htons(serv_port);

    // Bind to the local address

    if (bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        die("bind failed");

    // Start listening for incoming connections

    if (listen(servsock, 5 /* queue size for connection requests */ ) < 0)
        die("listen failed");

    int clntsock;
    socklen_t clntlen;
    struct sockaddr_in clntaddr;


    // +-------------------------------------------
    // part2 b

    // create a mdb-lookup-server sock, now I'm a client to mdb-lookup-server, and as a client, I only need server sock.

    char *mdb_serverName = argv[3];
    char *mdb_serverIP;
    unsigned short mdb_serverPort = atoi(argv[4]);


    int mdb_sock;
    struct sockaddr_in mdb_serverAddr;
    struct hostent *mdb_he;

     
    // get mdb-lookup server ip from mdb-server name
    if ((mdb_he = gethostbyname(mdb_serverName)) == NULL) {
	die("gethostbyname failed");
    }
    mdb_serverIP = inet_ntoa(*(struct in_addr *)mdb_he->h_addr);

    // create socket
    if ((mdb_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	die("socket failed");
    }


    // construct mdb-lookup server address
    memset(&mdb_serverAddr, 0, sizeof(mdb_serverAddr));
    mdb_serverAddr.sin_family = AF_INET;
    mdb_serverAddr.sin_addr.s_addr = inet_addr(mdb_serverIP);
    mdb_serverAddr.sin_port = htons(mdb_serverPort);

    // connect
    if (connect(mdb_sock, (struct sockaddr *)&mdb_serverAddr, sizeof(mdb_serverAddr)) < 0) {
	die("connect failed");
    }

    
    
    // wrap the socket with a file* so that we can read the socket using fgets()
    FILE *fd_mdb;
    if ((fd_mdb = fdopen(mdb_sock, "r")) == NULL) {
	die("fdopen failed mdb_sock");
    }



    // +-------------------------------------------

    //int count = 0;
    while (1) {

        //printf("\n$ %d \n", count++);

        char buf[4096];


        // Accept an incoming connection

        clntlen = sizeof(clntaddr); // initialize the in-out parameter

        if ((clntsock = accept(servsock,
                        (struct sockaddr * ) &clntaddr, &clntlen)) < 0){
            perror("clinet crash");
            //die("accept fail");
            continue; 
        }

        // accept() returned a connected socket (also called client socket)
        // and filled in the client's address into clntaddr


        // fd_clntsock, for clnt/browser
        FILE *fd_clntsock;  
        if ((fd_clntsock = fdopen(clntsock, "r")) == NULL) {   
           // if i cannot open clntsock, is it a clnt crash issue? No, my problem. die 
            die("fdopen failed");
        }



        // read GET request from FILE *fd_clntsock, clnt request from browser
        char requestLine[1000]; 
        if(fgets(requestLine, sizeof(requestLine), fd_clntsock) == NULL ){
            // fail to read request line, (maybe clnt crash/close connection -- fail to send request), skip current clnt to next one.
            // fprintf(stderr, "clnt crashes");
            fclose(fd_clntsock); //no need?
            continue;
        }

       // check fgets error 
       if (ferror(fd_clntsock)){
           perror("fd_clntsock error");
       }

        // parse browser http request line
        char *token_separators = "\t \r\n"; // tab, space, new line
        char *method = strtok(requestLine, token_separators);
        //  printf("1 method:(%s)", method);
        // printf("1 requestLine:(%s)", requestLine);
       
        char *requestURI = strtok(NULL, token_separators);
        // printf("2 requestURI:(%s)", requestURI);
        // printf("2 requestLine:(%s)", requestLine);
       
        char *httpVersion = strtok(NULL, token_separators);
        // printf("3 httpVersion:(%s)", httpVersion);
        // printf("3 requestLine:(%s)", requestLine);

        /*
           1 method:(GET)
           1 requestLine:(GET)
           2 requestURI:(/~yz4004/cs3157/tng/index.html)
           2 requestLine:(GET)
           3 httpVersion:(HTTP/1.1)
           3 requestLine:(GET)$ 1*/

        // print log through stderr, whether it's legal or not. if wrong put error code later.
        fprintf(stderr, "%s \"%s %s\" ",
                inet_ntoa(clntaddr.sin_addr),
                method,
                requestURI);




        // Now parse method and httpVersion first, and then requestURI. 
        // 1. check GET keyword
        if (strncmp(method, "GET", 3) != 0 ){ // 

            // fclose(fd_clntsock); no need to turn this off, since this clnt fails, we continue to next clnt (while 1)
            // fd_clntsock created again & cover old one. Not simple die program
            // as long as program keep running, no need to close/free since we do that at the end, unless die program.

            // send error 501 http to clnt & output log
            fprintf(stderr, "%d Not Implemented\n", 501); 

            char *html_501 = 
                "HTTP/1.0 501 Not Implemented\r\n\r\n"
                "<html><body><h1>501 Not Implemented</h1></body></html>";

            //printf("html : \n%s",html);
            if (send(clntsock, html_501, strlen(html_501), 0) != strlen(html_501)){
               //fclose(fd_mdb);
               fclose(fd_clntsock); 
               //die("send content failed");
               perror("send content failed");
            }

            continue;
        }
      
        // 2. check whether http 1.0 or 1.1 protocol
        if (strncmp("HTTP/1.0", httpVersion, 8) != 0 && strncmp("HTTP/1.1", httpVersion, 8) != 0) {
        
            fprintf(stderr, "%d Not Implemented\n", 501); 
            char *html_501 = 
                "HTTP/1.0 501 Not Implemented\r\n\r\n"
                "<html><body><h1>501 Not Implemented</h1></body></html>";

            if (send(clntsock, html_501, strlen(html_501), 0) != strlen(html_501)){
               //fclose(fd_mdb);
               fclose(fd_clntsock);
               //die("send content failed");
               perror("send content failed");
            }

            continue;
        }



        // 3. check URI starts with /, not ended with /..  not contains /../

        //printf("\n||||||| %s\n",requestURI);
        if (strncmp("/", requestURI, 1) != 0 || strstr(requestURI, "/../") || strstr(requestURI, "/..") )  {
        
            fprintf(stderr, "%d Bad Request\n", 400); 
            char *html_400 = 
                "HTTP/1.0 400 Bad Request\r\n\r\n"
                "<html><body><h1>400 Bad Request</h1></body></html>";

            if (send(clntsock, html_400, strlen(html_400), 0) != strlen(html_400)){
               //fclose(fd_mdb);
               fclose(fd_clntsock);
               //die("send content failed");
               perror("send content failed");
            }

            continue;
        }


        // printf("2333333333333333333333333333"); fflush(stdout);

         

       ///////////////   part 2 b

       // http://clac.cs.columbia.edu:41782/mdb-lookup 
       if (strcmp(requestURI, "/mdb-lookup") ==0 ){

           //printf("111111111111111  (%s), %d\n\n\n", requestURI, strcmp(requestURI, "/mdb-lookup"));
           fprintf(stderr, "200 OK\n");
           const char *form =
               "HTTP/1.0 200 OK\r\n"
               "\r\n"
               "<h1>mdb-lookup</h1>\n"
               "<p>\n"
               "<form method=GET action=/mdb-lookup>\n"
               "lookup: <input type=text name=key>\n"
               "<input type=submit>\n"
               "</form>\n"
               "<p>\n";

           if (send(clntsock, form, strlen(form), 0) != strlen(form) ){
               //fclose(fd_mdb);
               fclose(fd_clntsock);
               //die("send content failed");
               perror("send content failed");
           }

           //printf("\n\n send, you should see search page  \n\n");
           fclose(fd_clntsock);
           continue; 
      
       }

      
       // http://clac.cs.columbia.edu:41782/mdb-lookup?key=hello 
       if (strncmp(requestURI, "/mdb-lookup?key=",16) ==0 ){

           //printf("2222222222222222  (%s), %d\n\n\n", requestURI, strncmp(requestURI, "/mdb-lookup?key=",16 ));
           // printf("\n(%s)\n",requestURI);
           for(int i=0; i<16; i++){
               requestURI++;
           }
           strcat(requestURI, "\n");
        
           // printf("\n(%s)\n",requestURI);
           // send    
           if (send(mdb_sock, requestURI, strlen(requestURI), 0) != strlen(requestURI)) {
               //fclose(fd_mdb);
               fclose(fd_clntsock);
               //die("send failed");
               perror("send failed");
           }
          
       
           fprintf(stderr, "200 OK\n");
           strcpy(buf,
                   "HTTP/1.0 200 OK\r\n"     
                   "\r\n"
                   "<h1>mdb-lookup</h1>\n"
                   "<p>\n"
                   "<form method=GET action=/mdb-lookup>\n"
                   "lookup: <input type=text name=key>\n"
                   "<input type=submit>\n"
                   "</form>\n"
                   "<p>\n"
                   "<p><table border>\n");
    
           if( send(clntsock, buf, strlen(buf), 0) != strlen(buf) ){
               //fclose(fd_mdb);
               fclose(fd_clntsock);
               //die("send contenct failed 2b)");
               perror("send content failed");
           }

           char row[100];
           int even = 0;
           while(fgets(row, sizeof(row), fd_mdb)!= NULL){
               if( strcmp(row, "\n") == 0){
                   //printf("\n\n end \n\n");
                   break;
               }

               if(even++%2 == 0){
               
                   snprintf(buf, sizeof(buf), "<tr><td> %s\n", row);
               }else{
                   snprintf(buf, sizeof(buf), "<tr><td  bgcolor=yellow> %s\n", row);

               }
               if( send(clntsock, buf, strlen(buf), 0) != strlen(buf) ){
                   //fclose(fd_mdb);
                   fclose(fd_clntsock);
                   //die("send contenct failed 2b)");
                   perror("send content failed");
               }
    
           } // end while, fget from fb_mdb
       
           // check fgets fd_mdb 
           if (ferror(fd_mdb)){
               perror("fgets fd_mdb error");
           }
           fclose(fd_clntsock);
           continue; 
       }// end if ./mdb-lookup?key=



       // part2 a) continue  //////////

       // retrive the file -- requestURI
       // 1. make path
       char full_path[100];  // should not be " char *full_path;" has to have len
       strcpy(full_path, web_root);
       strcat(full_path, requestURI);  // char *file_path = strcat(web_root, requestURI);


       // int stat(const char *path, struct stat *buf);
       // success returns 0 & fill buf, error return -1
       // reference: https://www.ibm.com/docs/en/i/7.3?topic=ssw_ibm_i_73/apis/stat.htm 
       struct stat status;
       char full_path_1[strlen(full_path)];
       strcpy(full_path_1, full_path);



       // check ending char of path is '/', if true, concat  index.html 
       if(full_path_1[strlen(full_path_1)-1] == '/' ){
           strcat(full_path_1, "index.html");
       }
       
       
       // if path/file exists, proceeds, else  
       if(stat(full_path_1, &status) == 0){ // succeeds -- stat return none 0,  file not exists, then check directory/file

           //printf("**********  %s", full_path_1 );
       
       }else{

           //printf("**********  %s", full_path_1 );
           fprintf(stderr, "%d Not Found\n", 404); 
           if( strcmp(full_path,"/mnt/disks/students221/yz4004/html/cs3157/tng/favicon.ico" ) == 0 ){

               break;
           }


           //printf("\nfail does not exists:  %s\n", full_path_1 );
            char *html_404 = 
                "HTTP/1.0 404 Not Found\r\n\r\n"
                "<html><body><h1>404 Not Found</h1></body></html>";

            if (send(clntsock, html_404, strlen(html_404), 0) != strlen(html_404)){
                   //fclose(fd_mdb);
                   fclose(fd_clntsock);
                   //die("send content failed");
                   perror("send content failed");
            }

            continue;
       } 


       fprintf(stderr, "200 OK\n");


       // 2. prepare response headers
       snprintf(buf, sizeof(buf), 
               "HTTP/1.0 200 OK\r\n"
               "\r\n");

       // 3. open file, read & send
       FILE *file_requested = fopen(full_path_1, "rb");
       if( file_requested == NULL){ 
               fclose(fd_mdb);
               fclose(fd_clntsock);
               die("fail open file");
       }
       int size_read;

       size_read = strlen(buf); // should be 19, header 
       do{
           //printf("\n @@@@@@@@@@@@@@@@@@ %d \n",size_read); 
           if( send(clntsock, buf, size_read, 0) != size_read ){
               //fclose(fd_mdb);
               //fclose(file_requested);
               perror("send content failed");
               break;
               //fclose(fd_clntsock);
               //die("send content failed");
           }
       }while(( size_read = fread(buf,1, sizeof(buf), file_requested)) > 0);


       // fread() returns 0 on EOF or on error
       // so we need to check if there was an error.
       if (ferror(file_requested)){
           //fclose(fd_mdb);
           fclose(fd_clntsock);
           //die("fread failed");
           perror("fread failed");
       }
   
       

       fclose(file_requested);
       fclose(fd_clntsock);

       //fprintf(stdout, "\n");
    }// while (1)

    
 
    fclose(fd_mdb);
    return 0;
}
