import Sensor from "../models/usermodels.js";

// Post Data
export const createdataSensor = async (req, res) => {
  try {
    await Sensor.create(req.body);
    console.log(req.body);
    res.status(201).json({ msg: "Sensor Posted" });
  } catch (error) {
    console.log(error.message);
  }
};

export const getData = async (req, res) => {
  try {
    const response = await Sensor.findAll();
    res.status(200).json(response);
  } catch (error) {
    res.status(200).json("error cung");
    // console.log(error.message);
  }
};

/*
  (Get Post) http://127.0.0.1:5001/sensor
  {
    "curah_hujan" : 20,
    "cuaca" : "hujan ringan",
    "suhu" : 32,
    "kelembapan" : 78
  }
*/
