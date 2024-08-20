import { DataTypes } from "sequelize";
import db from "../database/db";

const SystemResource = db.define("system_resources", {
  id: {
    type: DataTypes.INTEGER,
    autoIncrement: true,
    primaryKey: true,
  },
  topic: {
    type: DataTypes.STRING,
  },
  name: {
    type: DataTypes.STRING,
  },
  total: {
    type: DataTypes.INTEGER,
  },
  usage: {
    type: DataTypes.TINYINT,
  },
  details: {
    type: DataTypes.STRING,
  },
});

export default SystemResource;
