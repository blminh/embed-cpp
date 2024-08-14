import express from "express";
import itemController from "../controllers/itemController";

const router = express.Router();
router.get("/items", itemController.itemsList);
router.get("/item?:id", itemController.getItem);
router.post("/add", itemController.addItem);

export default router;
