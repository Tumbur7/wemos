#include <ESP8266WiFi.h>

// di baggian ini menconectkan ke jaringan
const char* ssid     = "wifi2";
const char* password = "pasword00";

// untuk port server dan kita menggunakan port server  80
WiFiServer server(80);

// unutk menyimpan permintaan server http
String header;

// variabel bantuan utk menyimpan status keluaran saat ini
String output3State = "off";


// untuk pin inputan
const int output3 = D3;

void setup() {
  Serial.begin(115200);
  // unutk keluaran
  pinMode(output3, OUTPUT);
  
  // membuat hasil output LOW
  digitalWrite(output3, LOW);
  

  // terhubung ke wifi dengan ssdi dan pass
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // membuat alamat local dan mulai web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // melihat client yg masuk

  if (client) {                             // jika client yg terhubung,
    Serial.println("New Client.");          // cetak pesan di port serial
    String currentLine = "";                // membuat String untuk menyimpan data yang masuk dari klien
    while (client.connected()) {            // loop sementara klien terhubung
      if (client.available()) {             // jika ada byte untuk dibaca dari klien,
        char c = client.read();             // baca byte, lalu
        Serial.write(c);                    // cetaklah monitor serialnya
        header += c;
        if (c == '\n') {                    // jika byte adalah karakter baris baru
           // jika baris saat ini kosong, Anda mendapat dua karakter baris baru berturut-turut.
           // itulah akhir dari permintaan HTTP klien, jadi kirim respons:
           if (currentLine.length () == 0) {
             // Header HTTP selalu dimulai dengan kode respons (mis. HTTP / 1.1 200 OK)
             // dan tipe konten agar klien tahu apa yang akan terjadi, kemudian baris kosong:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // menyalakan dan mematikan GPIO
            if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            }
            
            // Tampilkan halaman web HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS untuk menata tombol on / off
             // Jangan ragu untuk mengubah warna latar dan atribut ukuran font agar sesuai dengan preferensi Anda
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Tajuk Halaman Web
            client.println("<body><h1>TA Kelompok 2</h1>");
            
            // Tampilkan status saat ini, dan tombol ON / OFF untuk Pin 3
            client.println("<p>GPIO 3 - State " + output3State + "</p>");
            // Jika output3 State mati, ini akan menampilkan tombol ON      
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            client.println("</body></html>");
            
            // Respons HTTP berakhir dengan baris kosong lain
            client.println();
            // Keluar dari loop sementara
            break;
          } else { // jika Anda mendapat baris baru, maka bersihkan currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // jika Anda mendapatkan hal lain selain karakter carriage return,
           currentLine += c; // tambahkan ke akhir currentLine
        }
      }
    }
    // Bersihkan variabel tajuk
    header = "";
    // tutup koneksi
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
