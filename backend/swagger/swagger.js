const swaggerJsdoc = require("swagger-jsdoc");

const options = {
  definition: {
    openapi: "3.0.0",
    info: {
      title: "My Express API",
      version: "1.0.0",
      description: "API documentation for a My Express app",
    },

    tags: [
      {
        name: "Login",
        description: "Login management"
      },

      {
        name: "Accounts",
        description: "Account management"
      },
      {
        name: "Cards",
        description: "Card management"
      },
      {
        name: "Cards & accounts",
        description: "Card accounts management"
      }
    ],

    servers: [
      {
        url: "http://localhost:3001",
      },
    ],

    components: {
      securitySchemes: {
        bearerAuth: {
          type: 'http',
          scheme: 'bearer',
          bearerFormat: 'JWT',
        },
      },
    },
    security: {
      bearerAuth: [],
    },
  },
  apis: ["./swagger/api_docs/*.yaml", "./swagger/swagger.js"], // files with annotations
};

const swaggerSpec = swaggerJsdoc(options);

module.exports = swaggerSpec;