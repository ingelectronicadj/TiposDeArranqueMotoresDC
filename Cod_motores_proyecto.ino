 #include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>


byte mac[] = { 0xDE, 0xA3, 0xBE, 0xEF, 0xFA, 0xE1 };
IPAddress ip(192,168,1,69);
//IPAddress gateway(192,168,1, 1);
//IPAddress subnet(255, 255, 255, 0);
// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
String readString = String(30);
void setup()
{
// start the Ethernet connection and the server:
Ethernet.begin(mac, ip);
server.begin();
pinMode(2,OUTPUT); //contactores
pinMode(3,OUTPUT); //kusa
pinMode(4,OUTPUT); //corto  kusa
pinMode(5,OUTPUT); //estatoricas
pinMode(6,OUTPUT); //corto estatoricas
pinMode(7,OUTPUT); //tiristores
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
            if(readString.indexOf("2=Encender")>0){
               digitalWrite(2,LOW);
               digitalWrite(3,LOW);
               digitalWrite(4,LOW);
               digitalWrite(5,LOW);
               digitalWrite(6,LOW);
               digitalWrite(7,LOW); 
               delay(3000);
               digitalWrite(2,HIGH);
               delay(8000);
               digitalWrite(2,LOW);
              }              
            if(readString.indexOf("3=Encender")>0){
                digitalWrite(2,LOW);
                digitalWrite(3,LOW);
                digitalWrite(4,LOW);
                digitalWrite(5,LOW);
                digitalWrite(6,LOW);
                digitalWrite(7,LOW);   
                delay(3000);
                digitalWrite(3,HIGH);
                //al haber encendido el aranque Kusa, espero 6 segundos y corto circuito la resistencia Kusa
                delay(6000);
                digitalWrite(4,HIGH);                         
                //despues de cortocircuitar la resistencia kusa espero 8 segundos y apago el arranque
                delay(8000);
                digitalWrite(3,LOW);
                digitalWrite(4,LOW);
               }           
            if(readString.indexOf("4=Encender")>0){
                digitalWrite(2,LOW);
                digitalWrite(3,LOW);
                digitalWrite(4,LOW);
                digitalWrite(5,LOW);
                digitalWrite(6,LOW);
                digitalWrite(7,LOW);             
                delay(30000);
                digitalWrite(5,HIGH);
                //al haber encendido el aranque Kusa, espero 6 segundos y corto circuito la resistencia Kusa
                delay(6000);
                digitalWrite(6,HIGH);
                delay(2000);
                digitalWrite(5,LOW);
                //despues de cortocircuitar la resistencia kusa espero 8 segundos y apago el arranque
                delay(8000);
                digitalWrite(6,LOW);
               }           
            if(readString.indexOf("5=Encender")>0){
               digitalWrite(2,LOW);
               digitalWrite(3,LOW);
               digitalWrite(4,LOW);
               digitalWrite(5,LOW);
               digitalWrite(6,LOW);
               digitalWrite(7,LOW);
               delay(30000);
               digitalWrite(7,HIGH);              
               }                 
           if(readString.indexOf("6=Apagar")>0){
               digitalWrite(2,LOW);
               digitalWrite(3,LOW);
               digitalWrite(4,LOW);
               digitalWrite(5,LOW);
               digitalWrite(6,LOW);
               digitalWrite(7,LOW);
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
client.println("<title>SOLO DISTRI</title>");
client.println("<style>body{background-color:#88F;}</style>");
client.println("</head>");
client.println("<body>");
client.println("<center>");
client.println("<h1>CENTRO DE CONTROL</h1>");
client.println("<hr><br>");
client.println("<h3>ARRANQUES PARA MOTOR TRIFASICO</h3>");
client.println("<hr><br>");
client.println("<table>");
client.println("<tr><td>CONFIG 1</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=2 value=Encender></form></td></tr>");
client.println("<tr><td>CONFIG 2</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=3 value=Encender></form></td></tr>");
client.println("<tr><td>CONFIG 3</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=4 value=Encender></form></td></tr>");
client.println("<tr><td>CONFIG 4</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=5 value=Encender></form></td></tr>");
client.println("<tr><td>CONFIG 5</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=6 value=Apagar></form></td></tr>");
client.println("</table>");
client.println("</center>");
client.println("<hr><br>");
client.println("</body>");
client.println("</html>");
client.stop();
}
}
}
}
}


