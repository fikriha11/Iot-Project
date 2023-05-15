import { React, useState, useEffect } from "react";
import WeatherApp from "./WeatherApp";
import TempApp from "./TempApp";
import HumiApp from "./HumiApp";
import axios from "axios";

function Body() {
  const [data, setUser] = useState([]);

  useEffect(() => {
    getUsers();
  }, []);

  const getUsers = async () => {
    const response = await axios.get("http://localhost:5001/sensor");
    setUser(response.data.pop());
  };

  return (
    <div className="chart">
      <div className="container-fluid">
        <h1 className="text-center mt-4">Monitoring Cuaca</h1>
        <br />
        <br />
        <div className="row justify-content-center">
          <div className="col-md-4">
            <TempApp value={data.suhu} time={data.createdAt} />
          </div>
          <div className="col-md-4">
            <WeatherApp
              value={data.curah_hujan}
              time={data.createdAt}
              weather={data.cuaca}
            />
          </div>
          <div className="col-md-4">
            <HumiApp value={data.kelembapan} time={data.createdAt} />
          </div>
        </div>
      </div>
    </div>
  );
}
export default Body;
