import router from "./routes/SensorRoute.js";
import express from "express";
import cors from "cors";

const app = express();

app.use(cors());
app.use(express.json());
app.use(router);
app.listen(5001, () => console.log(Date.now()));
