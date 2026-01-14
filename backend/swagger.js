const swaggerJsdoc = require("swagger-jsdoc");

const options = {
  definition: {
    openapi: "3.0.0",
    info: {
      title: "My Express API",
      version: "1.0.0",
      description: "API documentation for my Express app",
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
  apis: ["./routes/*.yaml", "./swagger.js"], // files with annotations
};

const swaggerSpec = swaggerJsdoc(options);

module.exports = swaggerSpec;