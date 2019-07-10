#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char ssid[] = "wifi2";                 // Network Name
char pass[] = "pasword00";                 // Network Password
byte mac[6];

WiFiServer server(80);
IPAddress ip(192,168,152,139);
IPAddress gateway(192,168,152,1);
IPAddress subnet(255, 255, 255, 0);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "INSERT INTO `pa2`.`t_data` (`tanggal`, `waktu`, `supporting_file`) VALUES ('2019-04-27', '14:00:00', 'OPEN');";
char query[255];

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
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  Serial.println("Connecting to database");
  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "Connected." );
  }
  Serial.println("");
  Serial.println("Connected to SQL Server!");  
}

void loop() {
  
  delay(1000); //1 sec
  Serial.println(query);
  sprintf(query, INSERT_SQL); // dibagian ini kita akan coba hilangkan, dan di bagian execute langsung kita panggil INSERT_SQL
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  //cur_mem->execute(INSERT_SQL); //di dalam execute antara insert_sql dan querry
  cur_mem->execute(query); 
  delete cur_mem; // dibagian ini antara di hapus atau tidak masih tidak dapat di pastikan
  Serial.println("Data recorded.");

}
