// according GLSL version to OpenGL 3.2 core profile
#version 150 core
#define PI 3.1415926538

// input into vertex shader (configured by vertex array configuration and filled from vertex buffer)
in vec2 in_vertex;

uniform vec2 offset;
uniform vec2 scale;

uniform sampler2D sprites;
uniform int currentDuration;
uniform int fullDuration;
uniform vec2 direction;
uniform int running;

// additional color output for this shader; will be interpolated among the 3 vertices building the triangle

out vec2 v_uv1a;
out vec2 v_uv1b;
out vec2 v_uv2a;
out vec2 v_uv2b;
out float dFrame;
out float dMove;

// TODO 2.1: add metadata of spriteset
vec2 startStand;
vec2 startRunning;
vec2 resizerStand;
vec2 resizerRunning;
ivec2 spriteXY1a;
ivec2 spriteXY1b;
ivec2 spriteXY2a;
ivec2 spriteXY2b;
const int nFramesPerLineStand = 58;
const int nFramesPerLineRunning = 45;
const int nFramesPerMoveStand = 16;
const int nFramesPerMoveRunning = 20;
const int nMovesStand = 16;
const int nMovesRunning = 32;


void getUV() {
	vec2 norm_vertex = (in_vertex + 1) / 2;			//Coords between 0..1
	ivec2 size = textureSize(sprites,0);
	ivec2 blockSizeStand = (size - ivec2(0, 2115)) / ivec2(nFramesPerLineStand, 5); //size - untererPart.y
	ivec2 blockSizeRunning = (size - ivec2(0, 665)) / ivec2(nFramesPerLineRunning, 15); //size - obererPart.y

	startStand = vec2(0, size.y - blockSizeStand.y);
	startRunning = vec2(0, 14*blockSizeRunning.y);

	ivec2 blockSize= ivec2(mix(blockSizeStand, blockSizeRunning, float(running > 0)));
	vec2 start = mix(startStand, startRunning, float(running > 0));

	int nFramesPerLine = int(mix(nFramesPerLineStand, nFramesPerLineRunning, float(running > 0)));
	int nFramesPerMove = int(mix(nFramesPerMoveStand, nFramesPerMoveRunning, float(running > 0)));

	float moveFrame = fract(float(currentDuration) / fullDuration) * nFramesPerMove;
	int moveFrame1 = int(floor(moveFrame)) % nFramesPerMove;
	//moveFrame1 = int(mix(moveFrame1 % (nFramesPerMove * 2), moveFrame1 % nFramesPerMove, float(running > 0)));
	//moveFrame1 = int(mix(moveFrame1, (nFramesPerMove * 2) - moveFrame1, float(moveFrame1 >= nFramesPerMove)));	
	int moveFrame2 = (moveFrame1 + 1) % nFramesPerMove;
	//moveFrame2 = int(mix(moveFrame2 % (nFramesPerMove * 2), moveFrame2 % nFramesPerMove, float(running > 0)));
	//moveFrame2 = int(mix(moveFrame2, (nFramesPerMove * 2) - moveFrame2, float(moveFrame2 >= nFramesPerMove)));

	dFrame = fract(moveFrame);

    float angle = atan(direction.y/direction.x);
    float revAngle = atan(direction.y/-direction.x);
    angle = mix(angle, angle + PI, float(direction.x < 0));
    angle = mix(angle, angle + (2*PI), float(angle < 0));

    int nMoves = int(mix(nMovesStand, nMovesRunning, float(running > 0)));

    float animationId = (angle/(PI)) * nMoves / 2;
    int aid1 = int(floor(animationId));
    int aid2 = int(floor(animationId + 1)) % nMoves;

    dMove = fract(animationId);

	//int frame1 = moveFrame1 + (animationId * nFramesPerMove);
	//int frame2 = moveFrame2 + (animationId * nFramesPerMove);
	int frame1a = moveFrame1 + (aid1 * nFramesPerMove);
	int frame1b = moveFrame1 + (aid2 * nFramesPerMove);
	int frame2a = moveFrame2 + (aid1 * nFramesPerMove);
	int frame2b = moveFrame2 + (aid2 * nFramesPerMove);

	spriteXY1a = ivec2(frame1a % nFramesPerLine, frame1a / nFramesPerLine);
	spriteXY1b = ivec2(frame1b % nFramesPerLine, frame1b / nFramesPerLine);
	spriteXY2a = ivec2(frame2a % nFramesPerLine, frame2a / nFramesPerLine);
	spriteXY2b = ivec2(frame2b % nFramesPerLine, frame2b / nFramesPerLine);

	//v_uv1 = (start + ((norm_vertex + spriteXY1) * blockSize)) / size;
	//v_uv2 = (start + ((norm_vertex + spriteXY2) * blockSize)) / size;
	v_uv1a = (start + ((norm_vertex + vec2(spriteXY1a.x, -spriteXY1a.y)) * blockSize)) / size;
	v_uv1b = (start + ((norm_vertex + vec2(spriteXY1b.x, -spriteXY1b.y)) * blockSize)) / size;
	v_uv2a = (start + ((norm_vertex + vec2(spriteXY2a.x, -spriteXY2a.y)) * blockSize)) / size;
	v_uv2b = (start + ((norm_vertex + vec2(spriteXY2b.x, -spriteXY2b.y)) * blockSize)) / size;
}	
/*
vec2 getUVWithAS(vec2 animationScale) {
	vec2 norm_vertex = (in_vertex + 1) * animationScale / 1.8;
	startStand = vec2(0.15, 19.92);
	startRunning = vec2(0.2, 14.77);
	//resizerStand = vec2(1.0/58,1.0/20);
	resizerStand = vec2(1.0/58-0.0000194,4.0/95+0.0058);
	resizerRunning = vec2(1.0/45,1.0/19-0.0022);
	int nFramesPerLine = int(mix(nFramesPerLineStand, nFramesPerLineRunning, float(running > 0)));
	vec2 start = mix(startStand, startRunning, float(running > 0));
	vec2 resizer = resizerStand;
	vec2 blockScale = mix(vec2(1), resizerRunning / resizerStand, float(running > 0));
	spriteXY = ivec2(int(currentDuration / speed) % nFramesPerLine, -int(currentDuration / speed / nFramesPerLine));
	//spriteXY = ivec2(0);
	return (norm_vertex + start + spriteXY * blockScale) * resizer;
}	*/

void main()
{
	//ORIGINAL!
    //vec2 animationScale = mix(vec2(0.75, 0.8), vec2(0.85, 1), float(running > 0));
	vec2 animationScale = mix(vec2(0.75, 0.8), vec2(0.95, 0.9), float(running > 0));

    gl_Position = vec4(in_vertex * scale * animationScale  + offset, 0.0, 1.0);

    // TODO 2.1: compute correct UV coordinates for spriteset texture lookup in fragment shader
    /*
    getUV -- clean, logic implementation -- can be fixed by changing animationScale...
	getUVWithAS -- try to use animationScale, so that running size fits standing size
			problem here: no matter how I scale the character, it's cut off or parts of neighbor sprites are visible..*/
    getUV();
}
