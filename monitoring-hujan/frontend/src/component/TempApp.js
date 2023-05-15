import React from "react";
import { Card } from "react-bootstrap";
import Datetime from "./Datetime";
import { FaTemperatureLow } from "react-icons/fa";

function TempApp({ value, time }) {
  return (
    <div className="d-flex justify-content-center align-items-center">
      <Card
        className="shadow-lg p-4 mb-5 bg-body rounded"
        style={{ width: "300px", height: "420px" }}
      >
        <Card.Body>
          <Card.Title className="text-center mb-4">Temperatur</Card.Title>
          <br />
          <div className="d-flex justify-content-center align-items-center mb-3">
            <FaTemperatureLow size={70} color="#0d6efd" />
          </div>
          <br />
          <div className="d-flex justify-content-center align-items-center mb-3">
            <h2>{Math.round(value)}°C </h2>
          </div>
          <div>
            <Datetime dateString={time} />
          </div>
        </Card.Body>
      </Card>
    </div>
  );
}

export default TempApp;
