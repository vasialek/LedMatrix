#pragma once

#include "randomprovider.h"
#include "ilogger.h"

struct MazeCell {
    int area;
    bool empty;
    bool rightWall;
    bool bottomWall;
};


class MazeBuilder
{
private:
    int _width;
    int _height;
    int _totalCells;
    char _logBuffer[512];
    IRandomProvider *_randomProvider = nullptr;
    ILogger *_logger = nullptr;
    MazeCell *_cells = nullptr;
    bool *_maze = nullptr;

    void BuildFirstLine();
    void BuildIntermediateLine(int currentLine);
    void BuildLastLine();
    bool DoBuildRightWall();
    bool DoBuildBottomWall();
    void ClonePreviousLine(int currentLine);
    void RemoveBottomWalls(int currentLine);
    void FillMissingAreas(int currentLine);
    void RemoveAllRightWalls(int currentLint) {
        for (auto x = 0; x < _width; x++)
        {
            _cells[GetIndex(currentLint, x)].rightWall = false;
        }

    }
    void Reset();
    int GetIndex(int x, int y) { return y * _height + x; }
public:
    MazeBuilder(IRandomProvider *randomProvider, ILogger *logger, int width, int height);

    void BuildLine(int line);
    bool *GetMaze();

    ~MazeBuilder();
};

MazeBuilder::MazeBuilder(IRandomProvider *randomProvider, ILogger *logger, int width, int height)
{
    _randomProvider = randomProvider;
    _logger = logger;
    _width = width;
    _height = height;
    _totalCells = width * height;
    _cells = new MazeCell[_totalCells];
    _maze = new bool[_totalCells];
    Reset();
}

void MazeBuilder::BuildLine(int line) {
    if (line == 0)
    {
        BuildFirstLine();
    } else if (line == _height - 1) {
        BuildLastLine();
    } else {
        BuildIntermediateLine(line);
    }
}

void MazeBuilder::BuildFirstLine() {
    int areaToSet = 1;
    int random = 0;
    for (auto x = 0; x < _width; x++)
    {
        auto index = GetIndex(x, 0);
        _cells[index].area = areaToSet++;
    }

    for (auto x = 0; x < _width; x++)
    {
        auto index = GetIndex(x, 0);

        bool buildRightWall = DoBuildRightWall();
        _cells[index].rightWall = !buildRightWall;
        if (!buildRightWall && x < _width - 1)
        {
            _cells[index + 1].area = _cells[index].area;
        }
    }

    for (auto x = 0; x < _width; x++)
    {
        auto index = GetIndex(x, 0);

        bool buildBottomWall = DoBuildBottomWall();
        _cells[index].bottomWall = buildBottomWall;
    }
}

void MazeBuilder::BuildIntermediateLine(int currentLine) {
    ClonePreviousLine(currentLine);
    RemoveAllRightWalls(currentLine);
}

void MazeBuilder::BuildLastLine() {
}

bool MazeBuilder::DoBuildRightWall() {
    int random = _randomProvider->Random(2);
    // sprintf(_logBuffer, "Random to build right wall: %d", random);
    // _logger->Debug(_logBuffer);
    return random == 1;
}

bool MazeBuilder::DoBuildBottomWall() {
    int random = _randomProvider->Random(2);
    // sprintf(_logBuffer, "Random to build bottom wall: %d", random);
    // _logger->Debug(_logBuffer);
    return random == 1;
}

void MazeBuilder::ClonePreviousLine(int currentLine) {
    int previousLineY = currentLine - 1;
    for (auto x = 0; x < _width; x++)
    {
        auto index = GetIndex(x, currentLine);
        auto indexPrevious = GetIndex(x, previousLineY);
        _cells[index].area = _cells[indexPrevious].area;
        _cells[index].rightWall = _cells[indexPrevious].rightWall;
        _cells[index].bottomWall = _cells[indexPrevious].bottomWall;
    }
}

void MazeBuilder::RemoveBottomWalls(int currentLine) {
    for (auto x = 0; x < _width; x++)
    {
        auto index = GetIndex(x, currentLine);
        if (_cells[index].bottomWall)
        {
            _cells[index].area = 0;
        }
        _cells[index].bottomWall = false;
    }
}

void MazeBuilder::FillMissingAreas(int currentLine) {
    int previousArea = 1;
    for (auto x = 0; x < _width; x++)
    {
        auto index = GetIndex(x, currentLine);
        if (_cells[index].area == 0)
        {
            _cells[index].area = previousArea;
        } else {
            previousArea = _cells[index].area;
        }
    }
}

bool *MazeBuilder::GetMaze() {
    for (auto y = 0; y < _height; y++)
    {
        for (auto x = 0; x < _width; x++)
        {
            auto index = GetIndex(x, y);
            _logBuffer[x] = '0' + _cells[index].area;
            if (_cells[index].rightWall && x < _width - 1)
            {
                _maze[index + 1] = true;
            }

            if (_cells[index].bottomWall && y < _height - 1)
            {
                auto bottomeIndex = GetIndex(x, y + 1);
                _maze[bottomeIndex] = true;
            }
        }
        _logBuffer[_width] = 0;
        _logger->Debug(_logBuffer);
    }

    return _maze;
}

void MazeBuilder::Reset() {
    for (auto y = 0; y < _height; y++)
    {
        for (auto x = 0; x < _width; x++)
        {
            auto index = GetIndex(x, y);
            _cells[index].empty = true;
            _maze[index] = false;
        }
    }
}

MazeBuilder::~MazeBuilder()
{
    delete []_cells;
    delete []_maze;
}
