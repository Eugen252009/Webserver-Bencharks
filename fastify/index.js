// Import the framework and instantiate it
import Fastify from 'fastify'
const fastify = Fastify({
  logger: false
})

// Declare a route
fastify.get('/', async function handler(request, reply) {
  return request.body
})

// Run the server!
try {
  await fastify.listen({ port: 3001 })
} catch (err) {
  fastify.log.error(err)
  process.exit(1)
}
