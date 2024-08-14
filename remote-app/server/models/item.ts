import { DataTypes } from "sequelize";
import db from "../database/db";

const Item = db.define("items", {
  id: {
    type: DataTypes.INTEGER,
    autoIncrement: true,
    primaryKey: true,
  },
  name: {
    type: DataTypes.STRING,
  },
  status: {
    type: DataTypes.TINYINT,
  },
});

export default Item;
