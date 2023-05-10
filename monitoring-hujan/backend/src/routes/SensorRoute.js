import express from "express";

import { createdataSensor, getData } from "../controller/SensorController.js";

const router = express.Router();

router.post("/sensor", createdataSensor);
router.get("/sensor", getData);

export default router;
