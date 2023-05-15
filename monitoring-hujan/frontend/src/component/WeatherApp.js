import { React } from "react";
import { Card } from "react-bootstrap";
import Datetime from "./Datetime";
import { TiWeatherCloudy, TiWeatherDownpour } from "react-icons/ti";

function WeatherApp({ value, time, weather }) {
  return (
    <div className="d-flex justify-content-center align-items-center">
      <Card
        className="shadow-lg p-4 mb-5 bg-body rounded"
        style={{ width: "300px", height: "420px" }}
      >
        <Card.Body>
          <Card.Title className="text-center mb-4">
            {" "}
            Intensitas Hujan
          </Card.Title>
          <div className="d-flex justify-content-center align-items-center mb-3">
            {value <= 20 ? (
              <TiWeatherCloudy size={70} color="#0d6efd" />
            ) : (
              <TiWeatherDownpour size={70} color="#0d6efd" />
            )}
          </div>
          <div className="d-flex justify-content-center align-items-center mb-3">
            <h2>
              {Math.round(value)}
              <span className="text-muted" style={{ fontSize: 12 }}>
                {" "}
                ml/min{" "}
              </span>
            </h2>
          </div>

          <div className="d-flex justify-content-center align-items-center">
            <p className="text-muted">{weather}</p>
          </div>
          <div>
            <Datetime dateString={time} />
          </div>
        </Card.Body>
      </Card>
    </div>
  );
}

export default WeatherApp;
