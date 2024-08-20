import bodyParser from "body-parser";
import cors from "cors";
import express from "express";
import db from "../database/db";
import itemRoutes from "../routes/item";
import systemRoutes from "../routes/system";

const app = express();
const port = 3000;

app.use(cors());
app.use(express.urlencoded({ extended: false }));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use("/", itemRoutes);
app.use("/", systemRoutes);

db.sync().then(() => {
  app.listen(port, () => {
    return console.log(`Express is listening at http://localhost:${port}`);
  });
});
