#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>

byte mac[] = { 0xDE, 0xA3, 0xBE, 0xEF, 0xFA, 0xE1 };
IPAddress ip(192,168,1,100);
//IPAddress gateway(192,168,1, 1);
//IPAddress subnet(255, 255, 255, 0);
// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

int PinLed1= 4; //esto sera actuador 1 
int PinLed2= 5; //esto sera actuador 2 
int PinLed3= 6; //esto sera actuador 3
int PinLed4= 7; //esto sera actuador 4
int PinLed5= 8; //esto sera actuador 5 

String readString = String(30);

void setup()
{
// start the Ethernet connection and the server:
Ethernet.begin(mac, ip);
server.begin();
pinMode(PinLed1,OUTPUT);
pinMode(PinLed2,OUTPUT);
pinMode(PinLed3,OUTPUT);
pinMode(PinLed4,OUTPUT);
pinMode(PinLed5,OUTPUT);
}

void loop()
{
// listen for incoming clients
EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
      boolean currentLineIsBlank = true; 
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
          if (readString.length()<100) //leer peticion HTTP caracter por caracter
          {
            readString += c;
          }
          if (c=='\n') //Si la peticion HTTP ha finalizado
            {
            //Determinar lo que se recibe mediante GET para encender el Led o apagarlo
            if(readString.indexOf("Led1=Encender")>0){
                digitalWrite(PinLed2,LOW);
                digitalWrite(PinLed3,LOW);
                digitalWrite(PinLed4,LOW);
                digitalWrite(PinLed5,LOW);
                delay(10000);  
              digitalWrite(PinLed1,HIGH);
              }    
            if(readString.indexOf("Led1=Apagar")>0){
                digitalWrite(PinLed1,LOW);
              }
            if(readString.indexOf("Led2=Encender")>0){
                digitalWrite(PinLed1,LOW);
                digitalWrite(PinLed3,LOW);
                digitalWrite(PinLed4,LOW);
                digitalWrite(PinLed5,LOW);
                delay(10000);
              digitalWrite(PinLed2,HIGH);
               }
            if(readString.indexOf("Led2=Apagar")>0){
                digitalWrite(PinLed2,LOW);
               }
            if(readString.indexOf("Led3=Encender")>0){
                digitalWrite(PinLed1,LOW);
                digitalWrite(PinLed2,LOW);
                digitalWrite(PinLed4,LOW);
                digitalWrite(PinLed5,LOW);
                delay(10000);  
                digitalWrite(PinLed3,HIGH);
               }
            if(readString.indexOf("Led3=Apagar")>0){
                digitalWrite(PinLed3,LOW);
               }
            if(readString.indexOf("Led4=Encender")>0){
                digitalWrite(PinLed1,LOW);
                digitalWrite(PinLed2,LOW);
                digitalWrite(PinLed3,LOW);
                digitalWrite(PinLed5,LOW);
                delay(10000);  
                digitalWrite(PinLed4,HIGH);
               }
            if(readString.indexOf("Led4=Apagar")>0){
                digitalWrite(PinLed4,LOW);
               }
            if(readString.indexOf("Led5=Encender")>0){
                digitalWrite(PinLed1,LOW);
                digitalWrite(PinLed2,LOW);
                digitalWrite(PinLed3,LOW);
                digitalWrite(PinLed4,LOW);
                delay(10000);  
                digitalWrite(PinLed5,HIGH);
               }
            if(readString.indexOf("Led5=Apagar")>0){
                digitalWrite(PinLed5,LOW);
               }
               
readString=""; //Vaciar el string que se uso para la lectura
//Enviar cabecera HTTP estandar
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
// client.println("Connection: close"); // the connection will be closed after completion of the response
// client.println("Refresh: 1"); // refresh the page automatically every 5 sec
client.println();
//Crear pagina web HTML
client.println("<html>");
client.println("<head>");
client.println("<title>Modos de arranques</title>");
client.println("</head>");
client.println("<body>");
client.println("<h1>MODOS DE ARRANQUE</h1>");
client.println("<hr><br>");
client.println("<h3>Encendido/Apagado de actuadores</h3>");
client.println("<hr><br>");
client.println("<table>");
client.println("<tr><td>Arranque 1</td><td>Arranque 2</td><td>Arranque 3</td><td>Arranque 4</td><td>Arranque 5</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=Led1 value=Encender></form></td><td><form method=get><input type=submit name=Led2 value=Encender></form></td><td><form method=get><input type=submit name=Led3 value=Encender></form></td><td><form method=get><input type=submit name=Led4 value=Encender></form></td><td><form method=get><input type=submit name=Led5 value=Encender></form></td></tr>");
client.println("<tr><td><form method=get><input type=submit name=Led1 value=Apagar></form></td><td><form method=get><input type=submit name=Led2 value=Apagar></form></td><td><form method=get><input type=submit name=Led3 value=Apagar></form></td><td><form method=get><input type=submit name=Led4 value=Apagar></form></td><td><form method=get><input type=submit name=Led5 value=Apagar></form></td></tr>");
client.println("</table>");
client.println("<hr><br>");

client.println("</body>");
client.println("</html>");
client.stop();


}
}
}
}
}

