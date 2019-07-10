#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>



char ssid[] = "ela";                 // Network Name
char pass[] = "tugasakhir2";                 // Network Password
byte mac[6];

WiFiServer server(80);
IPAddress ip(192,168,152,139);
IPAddress gateway(192,168,152,2);
IPAddress subnet(255, 255, 255, 0);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "INSERT INTO `pa2`.`t_data` (`tanggal`, `waktu`, `supporting_file`) VALUES ('2019-04-16', '14:00:00', 'OPEN')";
char query[128];

IPAddress server_addr(192,168,152,139);          // MySQL server IP
char user[] = "root";           // MySQL user
char password[] = "tumbur030";       // MySQL password

void setup() {
  Serial.begin(115200);
  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
//  WiFi.macAddress(mac);
//  Serial.print("MAC: ");
//  Serial.print(mac[5],HEX);
//  Serial.print(":");
//  Serial.print(mac[4],HEX);
//  Serial.print(":");
//  Serial.print(mac[3],HEX);
//  Serial.print(":");
//  Serial.print(mac[2],HEX);
//  Serial.print(":");
//  Serial.print(mac[1],HEX);
//  Serial.print(":");
//  Serial.println(mac[0],HEX);
//  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  Serial.println("Connecting to database");
  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }
  Serial.println("");
  Serial.println("Connected to SQL Server!");  
}

void loop() {
  
  delay(1000); //1 sec
  sprintf(query, INSERT_SQL);
  Serial.println("Recording data.");
  Serial.println(query);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(query);
  
//  delete cur_mem;

}
