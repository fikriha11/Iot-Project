import { Sequelize } from "sequelize";
import db from "../config/database.js";

const { DataTypes } = Sequelize;

const Sensor = db.define("curah_hujans", {
  curah_hujan: DataTypes.INTEGER,
  cuaca: DataTypes.STRING,
  suhu: DataTypes.INTEGER,
  kelembapan: DataTypes.INTEGER,
  createdAt: "2023-05-07 011:57:03",
});

export default Sensor;
