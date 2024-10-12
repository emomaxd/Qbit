using Qbit;

namespace Sandbox
{
    class Camera : Entity
    {
        Player player;
        TransformComponent playerTransform;
        private Vector2 initialDistance; 
        void OnCreate()
        {
            player = FindEntityByName("Player").As<Player>(); /* Gets the "Player" class from instance/object named as "Player" */
            playerTransform = player.GetComponent<TransformComponent>();

            float xDiff = Translation.X - player.Translation.X;
            float yDiff = Translation.Y - player.Translation.Y;
            initialDistance = new Vector2(xDiff, yDiff);
        }

        void OnUpdate(float ts)
        {
            float newCameraX = playerTransform.Translation.X + initialDistance.X;
            float newCameraY = playerTransform.Translation.Y + initialDistance.Y;
            Translation = new Vector3(newCameraX, newCameraY, Translation.Z);
        }
    }
}
