def time_to_points(t):
    """Convert MM:SS time to points."""
    max_minutes = 10
    m, s = t.split(':')
    total_seconds = int(m) * 60 + int(s)
    return max_minutes * 60 - total_seconds
