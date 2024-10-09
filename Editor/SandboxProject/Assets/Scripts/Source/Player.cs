using Qbit;

namespace Sandbox
{
    class Player : Entity
    {
        Rigidbody2DComponent rb;

        public float speed = 2.0f;
        public void OnCreate()
        {
            rb = GetComponent<Rigidbody2DComponent>();
        }
        public void OnUpdate(float ts)
        {
            //float Speed = speed;
            Vector3 velocity = Vector3.Zero;
            if (Input.IsKeyDown(KeyCode.W))
                velocity.Y = 1.0f;
            else if (Input.IsKeyDown(KeyCode.S))
                velocity.Y = -1.0f;

            if (Input.IsKeyDown(KeyCode.A))
                velocity.X = -1.0f;
            else if (Input.IsKeyDown(KeyCode.D))
                velocity.X = 1.0f;

            rb.ApplyLinearImpulse(velocity.XY * speed * ts, false);
        }
    }
}
