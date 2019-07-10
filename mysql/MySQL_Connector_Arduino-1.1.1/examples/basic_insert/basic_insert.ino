//#include <Ethernet.h>
//#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

//byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(192,168,152,139);  // IP of the MySQL *server* here
char user[] = "rootpa2";              // MySQL user login username
char password[] = "root";        // MySQL user login password

// Sample query
char INSERT_SQL[] = "INSERT INTO `pa2`.`t_data` (`tanggal`, `waktu`, `supporting_file`) VALUES ('2019-04-16', '14:00:00', 'OPEN')";

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect
//  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(100);
  }
  else
    Serial.println("Connection failed.");
}


void loop() {
  delay(2000);

  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(INSERT_SQL);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
}
