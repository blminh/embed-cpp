import express from "express";
import systemController from "../controllers/systemController";

const router = express.Router();
router.get("/apps", systemController.runningApps);
router.get("/app?:id", systemController.getApp);

export default router;
