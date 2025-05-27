#include <raylib.h>
#include <vector>
#include <raymath.h>

int main()
{


	const int SCREENWIDTH = 1280;
	const int SCREENHEIGHT = 720;

	const float OFFSET = 60;

	Rectangle Bounds = { OFFSET,OFFSET,SCREENWIDTH - 2*OFFSET,SCREENHEIGHT - 2*OFFSET };

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Motion");
	SetTargetFPS(60);
	int ParticleNumber = 500;

	std::vector<Vector2> ParticlePosition;
	int CurrentParticleNumber = 0;

	std::vector<Vector2> ParticleVelocity;
	Vector2 InitialVelocity = { 6,6 };

	std::vector<bool> ParticleCharge;

	float ParticleRadius = 14.0f;

	Vector2 CentreOfMass = { SCREENWIDTH/2,SCREENHEIGHT/2 };


	while (!WindowShouldClose()) {


		float dt = GetFrameTime();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CurrentParticleNumber<=ParticleNumber)
		{
			Vector2 MousePosition = GetMousePosition();
			ParticlePosition.push_back(MousePosition);
			CurrentParticleNumber++;

			int RandomNum = GetRandomValue(1, 4);
			switch (RandomNum)
			{
			case 1:
				InitialVelocity.x *= -1;
				ParticleVelocity.push_back(InitialVelocity);
				break;
			case 2:
				InitialVelocity.y *= -1;
				ParticleVelocity.push_back(InitialVelocity);
				break;
			case 3:
				InitialVelocity.x *= -1;
				InitialVelocity.y *= -1;
				ParticleVelocity.push_back(InitialVelocity);
				break;
			case 4:
				ParticleVelocity.push_back(InitialVelocity);
				break;

			default:
				break;
			}
			int RandomCharge = GetRandomValue(1, 2);
			switch (RandomCharge)
			{
			case 1:
				ParticleCharge.push_back(true);
				break;
			case 2:
				ParticleCharge.push_back(false);
				break;
			default:
				break;
			}
		}

		for (int i = 0;i < ParticlePosition.size();i++) {
			float TotalDistance = 0;
			for (int j = 0;j < ParticlePosition.size();j++) {
				float CurrentDistance=Vector2DotProduct(ParticlePosition[i], ParticlePosition[j])+1;
				if (ParticleCharge[i] ^ ParticleCharge[j] && i!=j) {
					TotalDistance = TotalDistance - (1 / ((CurrentDistance)));
				}

				else if (i == j) {
					TotalDistance += 0;
				}
				else {
					TotalDistance = TotalDistance + (1 / ((CurrentDistance)));
				}
			}
				ParticleVelocity[i].x += (TotalDistance);
				ParticleVelocity[i].y += (TotalDistance);
			
		}


        for (int i = 0; i < ParticlePosition.size(); i++) {
            for (int j = i + 1; j < ParticlePosition.size(); j++) {
                float dx = ParticlePosition[i].x - ParticlePosition[j].x;
                float dy = ParticlePosition[i].y - ParticlePosition[j].y;
                float distanceSq = dx * dx + dy * dy;
                float minDist = 2 * ParticleRadius;
                if (distanceSq <= minDist * minDist) {
                    Vector2 temp = ParticleVelocity[i]*DampingCoeff;
                    ParticleVelocity[i] = ParticleVelocity[j]*DampingCoeff;
                    ParticleVelocity[j] = temp;
                }
            }
            ParticlePosition[i] += ParticleVelocity[i];

            if (ParticlePosition[i].x >= Bounds.width - ParticleRadius + OFFSET || ParticlePosition[i].x <= Bounds.x+ParticleRadius) {
                ParticleVelocity[i].x *= -1;
                if (ParticlePosition[i].x >= Bounds.width - ParticleRadius + OFFSET) {
                    ParticlePosition[i].x = Bounds.width - ParticleRadius + OFFSET;
                } else {
                    ParticlePosition[i].x = Bounds.x+ParticleRadius;
                }
            }
            if (ParticlePosition[i].y >= Bounds.height - ParticleRadius + OFFSET || ParticlePosition[i].y <= Bounds.y+ParticleRadius) {
                ParticleVelocity[i].y *= -1;
                if (ParticlePosition[i].y >= Bounds.height - ParticleRadius + OFFSET) {
                    ParticlePosition[i].y = Bounds.height - ParticleRadius + OFFSET;
                } else {
                    ParticlePosition[i].y = Bounds.y+ParticleRadius;
                }
            }
        }

		for (int i = 0;i < ParticlePosition.size();i++) {
			CentreOfMass.x += ParticlePosition[i].x;
			CentreOfMass.y += ParticlePosition[i].y;
		}
		CentreOfMass.x /= ParticlePosition.size()+1;
		CentreOfMass.y /= ParticlePosition.size()+1;

		BeginDrawing();
		ClearBackground(DARKGRAY);
		DrawRectangleRounded(Bounds,0.03,0, LIGHTGRAY);
		

		for (int i = 0;i < ParticlePosition.size();i++) {
			if (ParticleCharge[i]) {
				DrawCircleV(ParticlePosition[i], ParticleRadius, YELLOW);
			}
			else {
				DrawCircleV(ParticlePosition[i], ParticleRadius, RED);
			}
		}

		DrawCircleLinesV(CentreOfMass, 30, BLACK);


		DrawText("Centre of Mass", 10, 18, 20, WHITE);
		DrawText(TextFormat("%d", (int)CentreOfMass.x-SCREENWIDTH/2), 180, 15, 30, SKYBLUE);
		DrawText(TextFormat("%d", (int)CentreOfMass.y - SCREENHEIGHT / 2), 270, 15, 30, SKYBLUE);
		DrawText("RANDOM PARTICLE COLLISION", SCREENWIDTH / 2 - 200, 15, 20, WHITE);
		DrawCircle(OFFSET, SCREENHEIGHT - OFFSET / 2, ParticleRadius, YELLOW);
		DrawText("- Positively Charged Particle",   OFFSET + ParticleRadius*1.5, SCREENHEIGHT - 2*OFFSET/3, 20, WHITE);
		DrawCircle(7*OFFSET, SCREENHEIGHT - OFFSET / 2, ParticleRadius, RED);
		DrawText("- Negatively Charged Particle", 7 * OFFSET + ParticleRadius * 1.5, SCREENHEIGHT - 2 * OFFSET / 3, 20, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}