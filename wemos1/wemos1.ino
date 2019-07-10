#include <TimeLib.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>

// di baggian ini menconectkan ke jaringan

const char* ssid = "wifi2";             
const char* pass = "pasword00";                


// untuk port server dan kita menggunakan port server  80
WiFiServer server(80);

// unutk menyimpan permintaan server http
String header;

// variabel bantuan utk menyimpan status keluaran saat ini
String output3State = "off";

// untuk pin inputan
const int output3 = D3;

// MySQL
char user[] = "root"; 
char password[] = "********";
IPAddress server_addr(192,168,152,139);
char INSER_DATA_WEMOS[] = "INSERT INTO `pa2`.`t_data` (`tanggal`, `waktu`, `supporting_file`) VALUES ('2019-04-15', '13:00:00', 'b')";
char query[128];

//connect led pin to d4 and ground
int ledPin = D4;          


time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

WiFiClient client;
MySQL_Connection conn((Client *)&client);


void setup() {
 Serial.begin(115200);
 // unutk keluaran
 pinMode(output3, OUTPUT);
 
 // membuat hasil output LOW
 digitalWrite(output3, LOW);
 
 delay(10);
 IPAddress ip(192,168,152,139);
 IPAddress subnet(255, 255, 255, 0);
 IPAddress gt(192,168,152,1);
 WiFi.config(ip, gt, subnet);
 WiFi.hostname("Wemos");
 
 // Connect to WiFi network
 WiFi.begin(ssid, pass);

 while ( WiFi.status() != WL_CONNECTED ) {
   delay ( 500 );
   Serial.print ( "." );
 }
 
 Serial.println ( "" );
 Serial.println ( "" );
 Serial.print ( "Connected to " );
 Serial.println ( ssid );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 Serial.println("DB - Connecting...");
 while (conn.connect(server_addr, 3306, user, password) != true) {
   delay(500);
   Serial.print ( "." );
 }

 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 setSyncProvider(getNtpTime);
 setSyncInterval(300);
 // Start the server
 server.begin();

}

void loop() {
  WiFiClient client = server.available();   // melihat client yg masuk

}
