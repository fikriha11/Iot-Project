import { Sequelize } from "sequelize";

const db = new Sequelize("hujan_db", "root", "", {
  host: "localhost",
  dialect: "mysql",
});

export default db;
