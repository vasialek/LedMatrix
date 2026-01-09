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
    int _mazeWidth;
    int _mazeHeight;
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
            _cells[GetCellIndex(currentLint, x)].rightWall = false;
        }

    }
    void BuildWallAt(int x, int y) {
        if (x < _mazeWidth - 1 && y < _mazeHeight - 1) {
            auto index = GetMazeIndex(x, y);
            // sprintf(_logBuffer, "(%d; %d) => %d", x, y, index);
            // _logger->Debug(_logBuffer);
            _maze[index] = true;
        }
    }
    void BuildBottomRightWallAt(int cellX, int cellY) {
        auto x = cellX * 2 + 1;
        auto y = cellY * 2 + 1;
        if (x < _mazeWidth && y < _mazeHeight) {
            auto index = GetMazeIndex(x, y);
            // sprintf(_logBuffer, "(%d; %d) => %d", x, y, index);
            // _logger->Debug(_logBuffer);
            _maze[index] = true;
        }
    }
    void Reset();
    int GetCellIndex(int x, int y) { return y * _height + x; }
    int GetMazeIndex(int x, int y) { 
        switch (y)
        {
        case 0:
            return x * 2;
        case 1:
            return 10 + x * 2;
        }
        return 2 * y * _mazeHeight + x;
    }
public:
    MazeBuilder(IRandomProvider *randomProvider, ILogger *logger, int width, int height);

    void BuildLine(int line);
    bool *GetMaze();
    void Test() {
        auto index = GetCellIndex(0, 0);
        // _cells[index].empty = false;
        // _cells[index].rightWall = true;
        // _cells[index].bottomWall = true;

        index = GetCellIndex(1, 1);
        _cells[index].empty = false;
        _cells[index].rightWall = true;
        _cells[index].bottomWall = true;
        // index = GetCellIndex(2, 2);
        // _cells[index].empty = false;
        // _cells[index].rightWall = true;
        // _cells[index].bottomWall = true;
        // index = GetCellIndex(3, 3);
        // _cells[index].empty = false;
        // _cells[index].rightWall = true;
        // _cells[index].bottomWall = true;
        // index = GetCellIndex(4, 4);
        // _cells[index].empty = false;
        // _cells[index].rightWall = true;
        // _cells[index].bottomWall = true;
    }

    ~MazeBuilder();
};

MazeBuilder::MazeBuilder(IRandomProvider *randomProvider, ILogger *logger, int width, int height)
{
    _randomProvider = randomProvider;
    _logger = logger;
    _width = width;
    _height = height;
    _mazeWidth = width * 2;
    _mazeHeight = height * 2;
    _totalCells = width * height;
    _cells = new MazeCell[_totalCells];
    _maze = new bool[_mazeWidth * _mazeHeight];  // add space for right and bottom walls
    Reset();
}

void MazeBuilder::BuildLine(int line) {
    // if (line == 0)
    // {
    //     BuildFirstLine();
    // } else if (line == _height - 1) {
    //     BuildLastLine();
    // } else {
    //     BuildIntermediateLine(line);
    // }
}

void MazeBuilder::BuildFirstLine() {
    // int areaToSet = 1;
    // int random = 0;
    // for (auto x = 0; x < _width; x++)
    // {
    //     auto index = GetCellIndex(x, 0);
    //     _cells[index].area = areaToSet++;
    // }

    // for (auto x = 0; x < _width; x++)
    // {
    //     auto index = GetCellIndex(x, 0);

    //     bool buildRightWall = DoBuildRightWall();
    //     _cells[index].rightWall = !buildRightWall;
    //     if (!buildRightWall && x < _width - 1)
    //     {
    //         _cells[index + 1].area = _cells[index].area;
    //     }
    // }

    // for (auto x = 0; x < _width; x++)
    // {
    //     auto index = GetCellIndex(x, 0);

    //     bool buildBottomWall = DoBuildBottomWall();
    //     _cells[index].bottomWall = buildBottomWall;
    // }
}

void MazeBuilder::BuildIntermediateLine(int currentLine) {
    // ClonePreviousLine(currentLine);
    // RemoveAllRightWalls(currentLine);
}

void MazeBuilder::BuildLastLine() {
}

bool MazeBuilder::DoBuildRightWall() {
    return false;
    // int random = _randomProvider->Random(2);
    // // sprintf(_logBuffer, "Random to build right wall: %d", random);
    // // _logger->Debug(_logBuffer);
    // return random == 1;
}

bool MazeBuilder::DoBuildBottomWall() {
    return false;
    // int random = _randomProvider->Random(2);
    // // sprintf(_logBuffer, "Random to build bottom wall: %d", random);
    // // _logger->Debug(_logBuffer);
    // return random == 1;
}

void MazeBuilder::ClonePreviousLine(int currentLine) {
    // int previousLineY = currentLine - 1;
    // for (auto x = 0; x < _width; x++)
    // {
    //     auto index = GetCellIndex(x, currentLine);
    //     auto indexPrevious = GetCellIndex(x, previousLineY);
    //     _cells[index].area = _cells[indexPrevious].area;
    //     _cells[index].rightWall = _cells[indexPrevious].rightWall;
    //     _cells[index].bottomWall = _cells[indexPrevious].bottomWall;
    // }
}

void MazeBuilder::RemoveBottomWalls(int currentLine) {
    // for (auto x = 0; x < _width; x++)
    // {
    //     auto index = GetCellIndex(x, currentLine);
    //     if (_cells[index].bottomWall)
    //     {
    //         _cells[index].area = 0;
    //     }
    //     _cells[index].bottomWall = false;
    // }
}

void MazeBuilder::FillMissingAreas(int currentLine) {
    // int previousArea = 1;
    // for (auto x = 0; x < _width; x++)
    // {
    //     auto index = GetCellIndex(x, currentLine);
    //     if (_cells[index].area == 0)
    //     {
    //         _cells[index].area = previousArea;
    //     } else {
    //         previousArea = _cells[index].area;
    //     }
    // }
}

bool *MazeBuilder::GetMaze() {
    for (auto y = 0; y < _height; y++) {
        for (auto x = 0; x < _width; x++) {
            auto index = GetCellIndex(x, y);
            // sprintf(_logBuffer, "Cell #%d, empty: %d, right: %d, bottom: %d", index, _cells[index].empty, _cells[index].rightWall, _cells[index].bottomWall);
            // _logger->Debug(_logBuffer);
            // if (!_cells[index].empty) {
            //     BuildWallAt(x, y);
            // }
            
            // if (_cells[index].rightWall) {
            //     BuildWallAt(x + 1, y);
            // }

            // if (_cells[index].bottomWall) {
            //     BuildWallAt(x, y + 1);
            // }

            auto mazeX = x * 2;
            auto mazeY = y * 2;
            auto mazeIndex = GetMazeIndex(mazeX, mazeY);
            _maze[mazeIndex] = ACOLOR_BLUE;

            // BuildBottomRightWallAt(x, y);
            // _logBuffer[x] = '0' + _cells[index].area;
            // if (_cells[index].rightWall && x < _width - 1)
            // {
            //     _maze[index + 1] = true;
            // }

            // if (_cells[index].bottomWall && y < _height - 1)
            // {
            //     auto bottomeIndex = GetIndex(x, y + 1);
            //     _maze[bottomeIndex] = true;
            // }
        }
        // _logBuffer[_width] = 0;
        // _logger->Debug(_logBuffer);
    }

    return _maze;
}

void MazeBuilder::Reset() {
    for (auto y = 0; y < _height; y++) {
        for (auto x = 0; x < _width; x++) {
            auto index = GetCellIndex(x, y);
            sprintf(_logBuffer, "Cearing cell at %d", index);
            _logger->Debug(_logBuffer);

            _cells[index].empty = true;
            _cells[index].rightWall = false;
            _cells[index].bottomWall = false;
        }
    }

    for (auto y = 0; y < _mazeHeight; y++)
    {
        for (auto x = 0; x < _mazeWidth; x++)
        {
            auto index = GetMazeIndex(x, y);
            sprintf(_logBuffer, "Cearing maze at %d", index);
            _logger->Debug(_logBuffer);
            _maze[index] = false;
            // _maze[mazeIndex + 1] = false;
            // mazeIndex = GetMazeIndex(x, y + 1);
            // _maze[mazeIndex] = false;
            // _maze[mazeIndex + 1] = false;
        }
    }
    
}

MazeBuilder::~MazeBuilder()
{
    delete []_cells;
    delete []_maze;
}
