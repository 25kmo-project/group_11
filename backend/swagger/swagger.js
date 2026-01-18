const swaggerJsdoc = require("swagger-jsdoc");

const options = {
  definition: {
    openapi: "3.0.0",
    info: {
      title: "Bank database API",
      version: "1.0.0",
      description: "API documentation for a bank database",
    },
    servers: [
      {
        url: "http://localhost:3001",
      },
    ],
    components: {
      securitySchemes: {
        JWT: {
          type: 'apiKey',
          in: 'header',
          name: 'access_token',
        },
      },
    },
  },
  apis: ["./swagger/api_docs/*.yaml", "./swagger/swagger.js"], // files with annotations
};

const swaggerSpec = swaggerJsdoc(options);

module.exports = swaggerSpec;