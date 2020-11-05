
class Player {

    public:
        Player();
        int checkLoop(double rayAngle);
        int prepareCollision(double angulo);
        int rayCast();

        double angle;

        float xPos;
        float yPos;

        float colXX;
        float colXY;
        float colYX;
        float colYY;

        float texturePosition;

        float distance;

};
