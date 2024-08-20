import expressAsyncHandler from "express-async-handler";
import mqtt from "mqtt";
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

const changeItemStatus = expressAsyncHandler(async (req, res) => {
  let status: any = req.query.status;
  console.log(`Status: ${status}`);

  const client = mqtt.connect("http://0.0.0.0:1883");
  client.on("connect", () => {
    console.log("Connect to mqtt!");

    client.publish("led", "1", (err) => {
      if (err) {
        console.error("Subscribe error:", err);
      } else {
        console.log("Message published successfully");
      }
      client.end();
    });
  });

  client.on("error", (err) => {
    console.error("Client error:", err);
  });
});

export default { itemsList, addItem, getItem, changeItemStatus };
