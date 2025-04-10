Sustav za radi tako da nudi korisniku da unese broj sekundi (0-9) za treptanje LED diode. Kada unesemo broj, toliko puta LED dioda treperi te nakon toga Arduino prelazi u Sleep mode. Kada se probudi javi obavijest te omogućuje pritisak na tipkalo koje omogućuje pokretanje simulacije PIR senzora (senzora pokreta). Nakon što pokrenemo Simulate Motion na senzoru, uključi se alarm kojeg čujemo preko buzzer-a. U tom trenutku druga LED dioda je upaljena dok ne gasimo alarm. Kako bi isključili alarm trebamo kliknuti na tipku # na tipkovnici. Kada isključimo alarm, možemo deaktivirati simulaciju i pritiskom ponovo na tipkalo aktivirati kako bi senzor bio aktivan i čekao da se detektira pokret, odnosno u našem slučaju pokrene Simulate Motion. Navedeni sustav može biti koristan u automatiziranim sustavima gdje je velika potreba za uštedom energije, a ujedno imaju i sigurnost zaštite putem senzora. 


## Grafikon strukture - "Prikaz strukture sustava s komponentama i njihovim međusobnim vezama"
![slika za GIT](https://github.com/user-attachments/assets/697f12ce-633d-4a43-964e-b7177742eaf8)


## Komponente

| Komponenta        | Količina | Pin na Arduino Uno        | 
|-------------------|----------|---------------------------|
| Arduino Uno       | 1        | -                         |
| Tipkalo           | 1        | GIO2 (Pin 2), GND              |
| PIR senzor        | 1        | GIO7 (Pin 7), GND, VCC (5V)              |
| Crvena LED        | 1        | GIO13 (Pin 13), GND            |
| Zelena LED        | 1        | GIO12 (Pin 12), GND            |
| Otpornik 220Ω     | 1        |  Između Crvene LED diode, odnosno Anode (pozitivne strane) i PIN 13|
| Otpornik 220Ω     | 1        |  Između Zelene LED diode, odnosno Anode (pozitivne strane) i PIN 12|
| Buzzer            | 1        | A0 (Pin A0), GND               |
| Keypad            | 1        | GIO3, GIO4, GIO5, GIO6 (Pin 3-6 za redove, GIO8, GIO9, GIO10, GIO11 za stupce) |

## Funkcionalni zahtjevi

# Funkcionalni zahtjevi sustava

| ID  | Funkcionalnost                                      | Opis                                                                                     | Prioritet |
|-----|-----------------------------------------------------|------------------------------------------------------------------------------------------|-----------|
| FR1 | Unos broja sekundi za treptanje LED diode           | Korisnik unosi broj sekundi (0-9) putem tipkovnice, što određuje broj treptaja LED diode. | Visok     |
| FR2 | Treptanje LED diode prema unosu                    | Nakon unosa, LED dioda trepće onoliko puta koliko je uneseno sekundi.                   | Visok     |
| FR3 | Prelazak u Sleep mode nakon treptanja               | Nakon završetka treptanja LED diode, Arduino prelazi u Sleep mode na 4 sekunde.           | Visok     |
| FR4 | Obavijest nakon buđenja iz Sleep moda               | Nakon buđenja iz Sleep moda, sustav šalje obavijest putem serijskog monitora.            | Srednji   |
| FR5 | Omogućavanje simulacije PIR senzora uz tipkalo     | Pritiskom na tipkalo omogućava se simulacija PIR senzora za detekciju pokreta.           | Visok     |
| FR6 | Aktivacija alarma prilikom detekcije pokreta       | Kada PIR senzor detektira pokret, alarm se aktivira (buzzer i LED dioda).                 | Visok     |
| FR7 | Isključivanje alarma pritiskom na # tipku           | Pritiskom na # tipku na tipkovnici korisnik isključuje alarm i LED diodu.                 | Visok     |
| FR8 | Deaktivacija simulacije PIR senzora                | Nakon isključivanja alarma, korisnik može ponovo pritisnuti tipkalo za deaktivaciju simulacije. | Srednji   |
| FR9 | Ponovno aktiviranje PIR senzora za detekciju pokreta | Pritiskom na tipkalo korisnik aktivira PIR senzor koji čeka detekciju pokreta.          | Visok     |
| FR10| Prikaz statusa na serijskom monitoru                | Sustav ispisuje status operacija na serijskom monitoru, uključujući početak treptanja, aktivaciju alarma i status simulacije. | Srednji   |


## Plan ispitivanja, rezultati ispitivanja

Test 1: Nudi korisniku mogućnost unosa broja (0-9), odnosno treptaja crvene LED diode  
Proces: Nakon svakog unosa crvena LED dioda treperi uneseni broj puta
Status: Prošlo, uspješno radi

Test 2: Arduino ide 4 sekunde u Sleep mode i javlja kad se probudi 
Proces: Arduino ulazi u Sleep mode i nakon 4 sekunde mora javiti poruku da se probudio i omogućuje pritisak tipkala  
Status: Prošlo, uspješno radi

Test 3: Pritiskom na tipkalo aktiviramo simulaciji i deaktiviramo 
Proces: Klikom na tipkalo, omogućimo simulaciju senzora i ispisuje pokret detektiran, alarm aktiviran i isključi #. Svijetli Zelena LED dioda. 
Status: Prošlo, uspješno radi

Test 4: Isključenje i ponovno aktiviranje alarma
Proces: Isključimo alarm na #. Jednim klikom na tipkalo deaktiviramo simulaciju alarma, a još jednim ponovno aktiviramo i možemo pokrenuti simulaciju alarma.   
Status: Prošlo, uspješno radi  

Test 5: Testiranje više ciklusa  
Proces: Nakon 10 uzastopnih testiranja sve radi bez greške  
Status: Prošlo, uspješno radi  

## Link za projekt na Wokwi stranici je: https://wokwi.com/projects/427103544553672705


