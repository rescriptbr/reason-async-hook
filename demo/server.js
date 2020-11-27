const fastify = require("fastify")({ logger: true });

fastify.register(require("fastify-cors"), {
  origin: /.*/,
  allowedHeaders: [
    "Origin",
    "X-Requested-With",
    "Accept",
    "Content-Type",
    "Authorization",
  ],
  methods: ["GET", "PUT", "PATCH", "POST", "DELETE", "OPTIONS"],
});

fastify.get("/user", (_request, reply) => {
  reply.send({
    name: "Foo",
    age: 42,
  });
});

const start = async () => {
  try {
    await fastify.listen(3000);
    fastify.log.info(`Server listening on ${fastify.server.address().port}`);
  } catch (err) {
    fastify.log.error(err);
    process.exit(1);
  }
};

start();
