
#include <Wire.h> 
#include <MPU6050.h> 
#include <TinyGPS++.h> 
#include <SoftwareSerial.h> 
#define IR_SENSOR A0 
#define VIBRATION_PIN 5 
#define BUZZER_PIN 11 
SoftwareSerial gsm(9,8),gpsSerial(4,3); 
MPU6050 mpu; TinyGPSPlus gps; 
bool sleeping=false,accident=false,gpsReady=false; 
String latitude="",longitude=""; 
int16_t accX,accY,accZ,gyroX,gyroY,gyroZ; 
float initialPitch=0,initialRoll=0; 
const char bikerNumber[]="+917709543463",emergencyNumber[]="+917709543463"; 
int tiltThreshold=90,irThreshold=200; 
void setup(){ 
Serial.begin(9600); gsm.begin(9600); gpsSerial.begin(9600); 
Wire.begin(); mpu.initialize(); 
pinMode(IR_SENSOR,INPUT); pinMode(VIBRATION_PIN,INPUT); 
pinMode(BUZZER_PIN,OUTPUT); digitalWrite(BUZZER_PIN,LOW); 
Serial.println("Initializing MPU6050..."); 
if(!mpu.testConnection()){ Serial.println("MPU6050 connection failed!"); while(1); } else 
Serial.println("MPU6050 connected successfully!"); 
 delay(1000); 
  Serial.println("Taking initial orientation readings... Keep helmet still..."); 
  delay(2000); calibrateMPU(); 
 
  Serial.println("Initializing GPS module..."); 
  waitForGPSFix(); 
  Serial.println("GPS Initialized. System Started."); 
  delay(1000);} 
 
void loop(){ updateGPS(); checkSleep(); checkSensors(); delay(200); } 
 
void checkSleep(){ 
  static unsigned long eyeCloseStart=0; 
  int irValue=analogRead(IR_SENSOR); 
  if(irValue<irThreshold){ 
    if(!eyeCloseStart)eyeCloseStart=millis(); 
    if(millis()-eyeCloseStart>=5000&&!sleeping){ 
      sleeping=true; Serial.println("Drowsiness detected! Activating buzzer..."); 
      digitalWrite(BUZZER_PIN,HIGH); delay(10000); 
      digitalWrite(BUZZER_PIN,LOW); sleeping=false; eyeCloseStart=0;}}  
else eyeCloseStart=0;} 
 
void calibrateMPU(){ 
  long ax=0,ay=0,az=0; 
  for(int i=0;i<100;i++){ mpu.getAcceleration(&accX,&accY,&accZ); ax+=accX; ay+=accY; 
az+=accZ; delay(10); } 
  accX=ax/100; accY=ay/100; accZ=az/100; 
  initialPitch=atan2(accY,sqrt(accX*accX+accZ*accZ))*180.0/PI; 
  initialRoll=atan2(-accX,accZ)*180.0/PI; 
  Serial.print("Initial Pitch: ");Serial.println(initialPitch); 
  Serial.print("Initial Roll : ");Serial.println(initialRoll); 
  Serial.println("-------------------------------------------");} 
 
void checkSensors(){ 
  static bool lastAccident=false; 
  int vibState=digitalRead(VIBRATION_PIN),irValue=analogRead(IR_SENSOR); 
  mpu.getMotion6(&accX,&accY,&accZ,&gyroX,&gyroY,&gyroZ); 
 
  float pitchNow=atan2(accY,sqrt(accX*accX+accZ*accZ))*180.0/PI; 
  float rollNow=atan2(-accX,accZ)*180.0/PI; 
  float pitchChange=pitchNow-initialPitch,rollChange=rollNow-initialRoll; 
 
  Serial.print("IR: ");Serial.print(irValue); 
  Serial.print(" | Vibration: ");Serial.print(vibState); 
  Serial.print(" | PitchChange: ");Serial.print(pitchChange); 
  Serial.print(" | RollChange: ");Serial.print(rollChange); 
  Serial.print(" | latitude: ");Serial.print(latitude); 
  Serial.print(" | longitude: ");Serial.println(longitude); 
 
  bool accidentNow=false; String reason=""; 
  if(vibState==LOW){ accidentNow=true; reason+="Vibration sensor triggered. "; } 
  if(abs(pitchChange)>=tiltThreshold||abs(rollChange)>=tiltThreshold){ accidentNow=true; 
reason+="Helmet tilted > 90°. "; } 
  if(accidentNow&&!lastAccident){ 
    Serial.println("Accident detected!"); Serial.print("Reason: "); Serial.println(reason); 
    handleAccident();} 
  lastAccident=accidentNow;} 
void updateGPS(){ 
  while(gpsSerial.available())gps.encode(gpsSerial.read()); 
gps.location.isValid()?(latitude=String(gps.location.lat(),6),longitude=String(gps.location.lng(),6),gp
sReady=true):gpsReady=false;} 
void waitForGPSFix(){ 
  unsigned long t=millis(); bool fix=false; 
  while(!fix){ 
    while(gpsSerial.available()){ gps.encode(gpsSerial.read()); if(gps.location.isValid()){ fix=true; 
break; } } 
    if(!fix && millis()-t>10000){ Serial.println("Waiting for GPS signal..."); t=millis(); }} 
  latitude=String(gps.location.lat(),6); longitude=String(gps.location.lng(),6); gpsReady=true; 
  Serial.print("GPS Fix Acquired! Latitude: ");Serial.print(latitude); 
  Serial.print(" | Longitude: ");Serial.println(longitude);} 
 
void handleAccident(){ 
  if(!gpsReady){ Serial.println("GPS not ready. Waiting for fix before calling..."); waitForGPSFix(); 
} 
  Serial.println("Calling biker for confirmation..."); 
  makeCall(bikerNumber); delay(40000); endCall(); 
 
  bool bikerResponded=checkBikerResponse(); 
  if(!bikerResponded){ 
    Serial.println("No response. Calling emergency contact..."); 
    makeCall(emergencyNumber); delay(30000); endCall(); sendSMS();}  
 else Serial.println("Biker responded. No emergency call made.");} 
 
void makeCall(const char *number){ gsm.print("ATD"); gsm.print(number); gsm.println(";"); 
Serial.print("Dialing: "); Serial.println(number); } 
void endCall(){ gsm.println("ATH"); Serial.println("Call ended."); } 
bool checkBikerResponse(){ return false; } 
 
void sendSMS(){ 
  if(!gpsReady){ Serial.println("Cannot send SMS - GPS not ready."); return; } 
  String msg="Accident detected!\nLocation: https://maps.google.com/?q="+latitude+","+longitude; 
gsm.println("AT+CMGF=1"); delay(1000); 
gsm.print("AT+CMGS=\""); gsm.print(emergencyNumber); gsm.println("\""); 
delay(1000); gsm.print(msg); gsm.write(26); delay(3000); 
Serial.println("SMS sent with location.");}