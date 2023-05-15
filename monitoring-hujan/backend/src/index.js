import router from "./routes/SensorRoute.js";
import express from "express";
import cors from "cors";

const port = 5001;
const app = express();

app.use(cors());
app.use(express.json());
app.use(router);
app.listen(port, () =>
  console.log(`Aplikasi Express.js berjalan di http://localhost:${port}`)
);
