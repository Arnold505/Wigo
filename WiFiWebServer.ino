#include <SPI.h>
#include <WiFi101.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "lg";
char pass[] = "12345678";// your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

#define TRIGGER1 1
  #define ECHO1    0

  #define TRIGGER2 6  
  #define ECHO2    5

    int cont=0;
    
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  
  Serial.begin (9600);
  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status
}



void loop() {

  
  long duration1, distance1;
  long duration2, distance2;
  
  digitalWrite(TRIGGER1, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER1, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER1, LOW);
  duration1 = pulseIn(ECHO1, HIGH);
  distance1 = duration1/58;
  
//PRIMER SENSOR ULTRASONICO

  digitalWrite(TRIGGER2, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER2, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER2, LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 = duration2/58;

 if(distance1<6){
      cont++;
      Serial.print("Entró una persona, así que hay: ");
      Serial.println(cont);
      delay(1000);
 }
    else if (distance2<6){
      cont--;
      Serial.print("Salió una persona, así que hay: ");
      Serial.println(cont);
      delay(1000);
      }
      Serial.println(cont);
      delay(1000);

    
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
              
            // the content of the HTTP response follows the header:
            
           client.println("<!DOCTYPE html>");
client.println("<html>");
  client.println("<head>");
  client.println("</head>");
client.println("<body>");

client.println("<center>");
  client.println("<h2>");
    client.println("control");
    client.println("</h2>");
client.println("</center>");



client.println("<table>");
    client.println("<tr>");

      client.println("<th>");
         client.println("Mesa");
      client.println("</th>");

      client.println("<th>");
         client.println("Estado");
      client.println("</th>");

      client.println("<th>");
         client.println("Usos");
      client.println("</th>");

    client.println("</tr>");

    client.println("<tr>");

      client.println("<td>");
       client.println("Mesa1");
      client.println("</td>");

      client.println("<td>");

      client.println("</td>");

      client.println("<td>");

      client.println("</td>");    

    client.println("</tr>");

    client.println("<tr>");

     client.println("<td>");
      client.println("Mesa2");
     client.println("</td>");

     client.println("<td>");

     client.println("</td>");
    
     client.println("<td>");

     client.println("</td>");   
   
    client.println("</tr>");
 
client.println("</table>");

client.println("</body>");
client.println("</html>");


          // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(6, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(6, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(
);
  
}




