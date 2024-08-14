import expressAsyncHandler from "express-async-handler";
import Item from "../models/item";

const itemsList = expressAsyncHandler(async (req, res) => {
  let items = await Item.findAll();
  res.json(items);
});

const getItem = expressAsyncHandler(async (req, res) => {
  console.log(req.params.id);
  console.log(req.query.id);
  let id: any = req.query.id;
  let item = await Item.findByPk(parseInt(id));
  res.json(item);
});

const addItem = expressAsyncHandler(async (req, res) => {
  let result = await Item.create(req.body);
  res.json(result);
});

export default { itemsList, addItem, getItem };
