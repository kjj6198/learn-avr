
void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    int result = Serial.read();
    Serial.println(result);
  }

  int result = digitalRead(2);
  Serial.print("DHT");
  Serial.println(result);
}