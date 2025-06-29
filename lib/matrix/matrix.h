#include "../vector/vector.h"

bool DownExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y);

bool LeftExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y);

bool RightExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y);

bool UpExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x);

bool MoreThanFour(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y);

void Scatter(Vector<Vector<uint64_t>>& mass, uint64_t max_x, uint64_t max_y);

void MakePicture(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y);

void IterationOfPicture(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y);