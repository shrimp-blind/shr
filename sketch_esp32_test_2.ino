#include <WiFi.h>
#include <WiFiClientSecure.h>
char ssid[] = "When Can My Internet Get Better";
char password[] = "O00O00O0";
String Linetoken = "MbcvZH9nf1mvsSkXBzEpoQDQNOaNkWpHJ2nmoSBSBpz";
WiFiClientSecure client; // 宣告一個加密的 WiFi 連線端
char host[] = "notify-api.line.me"; // 宣告 Line API 網站
String message = "這是 esp32 連接 line ";
int counter=0;
void setup() {
    Serial.begin(115200);
    Serial.print("Connecting Wifi: ");// 連線到指定的 WiFi ssid
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    // 連線成功，顯示取得的 IP
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
    client.setInsecure();
        String ts="";
    // 連線到 Line API 網站
    Serial.print("Connect to ");Serial.println(host);
    if (client.connect(host, 443)) {
        client.println("POST /api/notify HTTP/1.1");//(1)(2)傳遞網站
        client.print("Host: "); client.println(host); //Line API 網站
        client.println("Authorization: Bearer " + Linetoken);//(3)(4)(5)傳送權杖
        client.println("Content-Type: application/x-www-form-urlencoded");//(6)(7)資料內容
        counter++;
        ts = message + "(" + String(counter) + ")";//傳遞訊息
        client.println("Content-Length: " + String((ts.length() + 8)));//訊息長度 len("message=")=8
        client.println();
        client.println("message=" + ts); //(8)訊息內容
        // 等候回應
        delay(2000);
        String response = client.readString();
        Serial.println(response);// 顯示傳遞結果
        client.stop(); // 斷線，否則只能傳 5 次
    }
    else {//傳送失敗
        Serial.println("Line Api connected fail");
    }
}

void loop() {

    delay(10000);// 每 10 秒讀取一次溫濕度
}
