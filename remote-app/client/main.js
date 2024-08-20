async function listItems() {
  axios
    .get("http://0.0.0.0:3000/items")
    .then((res) => {
      console.log(res);
      const result = [];
      res.data.forEach((el) => {
        result.push({
          name: el.name,
          status: el.status == 1 ? "on" : "off",
        });
      });
      document.getElementById("items").appendChild(createTable(result));
    })
    .catch((err) => {
      console.log(err);
    });
}

function searchItem() {
  let val = document.getElementById("searchText").value;
  console.log("send msg " + val + "!");

  axios
    .get("http://0.0.0.0:3000/item", {
      params: {
        id: val,
      },
    })
    .then((res) => {
      console.log(res);
      document.getElementById(
        "item"
      ).innerHTML = `Name: ${res.data.name} | Status: ${res.data.status}`;
    })
    .catch((err) => {
      console.log(err);
    });
}

function changeItemStatus(val) {
  // let status = document.getElementById("ledStatus").selectedOptions[0].value;
  console.log("send msg " + val + "!");

  axios
    .get("http://192.168.100.9:3000/change", {
      params: {
        status: val,
      },
    })
    .catch((err) => {
      console.log(err);
    });
}

function createItem() {
  let name = document.getElementById("itemName").value;
  let status = document.getElementById("itemStatus").selectedOptions[0].value;

  axios
    .post("http://0.0.0.0:3000/add", {
      name,
      status,
    })
    .then(() => {
      listItems();
    })
    .catch((err) => {
      console.log(err);
    });
}

function createTable(data) {
  const table = document.createElement("table");
  table.setAttribute("border", "1");

  const headerRow = document.createElement("tr");
  Object.keys(data[0]).forEach((key) => {
    const th = document.createElement("th");
    th.appendChild(document.createTextNode(key));
    headerRow.appendChild(th);
  });
  table.appendChild(headerRow);

  data.forEach((item) => {
    const row = document.createElement("tr");
    Object.values(item).forEach((value) => {
      const td = document.createElement("td");
      td.appendChild(document.createTextNode(value));
      row.appendChild(td);
    });
    table.appendChild(row);
  });

  return table;
}
