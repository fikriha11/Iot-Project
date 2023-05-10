#define relay 9
#define SensorFlowA  2

struct SensorFlow {
  int Count;
} FlowA, FlowB;

String IR64 = "b";
int limit = 0;
void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(SensorFlowA, INPUT);
  attachInterrupt(digitalPinToInterrupt(SensorFlowA), pulseCounterA, CHANGE);
}

void loop() {
  if (Serial.available()) {
    IR64 = Serial.readStringUntil('\n');
    if (IR64 == "100") {
      limit = 1300;
      digitalWrite(relay, HIGH);
    } else if (IR64 == "200") {
      limit = 2300;
      digitalWrite(relay, HIGH);
    } else if (IR64 == "300") {
      limit = 3300;
      digitalWrite(relay, HIGH);
    } else if (IR64 == "400") {
      limit = 4100;
      digitalWrite(relay, HIGH);
    } else if (IR64 == "500") {
      limit = 5000;
      digitalWrite(relay, HIGH);
    }


    else if (IR64 == "b") {
      digitalWrite(relay, LOW);
    } else {
      FlowA.Count = 0;
    }

  }

  if ( FlowA.Count >= limit) {
    digitalWrite(relay, LOW);
    IR64 = "b";
  }

  Serial.println(FlowA.Count);
}

void pulseCounterA() {
  FlowA.Count++;
}
