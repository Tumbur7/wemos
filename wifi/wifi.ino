#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

const char* ssid = "wifi2";             //!!!!!!!!!!!!!!!!!!!!! modify this
const char* password = "pasword00";                //!!!!!!!!!!!!!!!!!!!!!modify this

int ledPin = D4;          //connect led pin to d4 and ground
int intensitas = 0;
WiFiServer server(80);

void setup() {
 Serial.begin(115200);
 delay(10);


 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);

 // Connect to WiFi network
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);

 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");

 // Start the server
 server.begin();
 Serial.println("Server started");

 // Print the IP address
 Serial.print("Use this URL : ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
}


void loop() {

  
  
 // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) {
   return;
 }

 // Wait until the client sends some data
 Serial.println("new client");
 while(!client.available()){
   delay(1);
 }

 // Read the first line of the request
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();

 // Match the request

 int value = LOW;
 if (request.indexOf("/LED=ON") != -1) { // request.indexOf = cari char atau string dalam string, -1 = tidak ditemukan
      if(intensitas >= 255)
     intensitas = 255;
     else
     intensitas+=20;
     analogWrite(ledPin, intensitas);
    
     
     value = HIGH; 
 } 
 if (request.indexOf("/LED=OFF") != -1){
   if(intensitas <= 0)
    { intensitas = 0;}
    else
     intensitas-=20;
     
     analogWrite(ledPin, intensitas);
     
     
   value = LOW;
 }



 // Return the response
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println(""); //  do not forget this one
 client.println("<!DOCTYPE HTML>");
 client.println("<?php");
 client.println("$db = mysqli_connect('localhost','root','tumbur030','pa2')");
 client.print  ("or die('Error connecting to MySQL server.')");
 client.println("<html>");
 client.println("<head>");
 client.println("</head>");
 client.println("<body>");
 client.println("<h1>PHP connect to MySQL</h1>");
 client.println("<?php>");
 client.println("$query = 'SELECT * FROM t_data'");
 client.println("\n");
 client.println("mysqli_query($db, $query) or die('Error querying database.')");
 client.println("$result = mysqli_query($db, $query)");
 client.println("$row = mysqli_fetch_array($result)");
 client.println("while ($row = mysqli_fetch_array($result))");
 client.print  ("{echo $row['id'] . ' ' . $row['tanggal'] . ': ' . $row['waktu'] . ' ' . $row['supporting_file'] .'<br />'}");
 client.println("mysqli_close($db)");
 client.println("?>");
 client.println("</body>");
 client.print("Led pin is now: ");

 if(value == HIGH) {
   client.print("On");  
 } else {
   client.print("Off");
 }
 client.println("<br><br>");
 client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 4 ON<br>");
 client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 4 OFF<br>");
 client.println("</html>");

 delay(1);
 Serial.println("Client disconnected");
 Serial.println("");

}
