def max_area(height):
    max_area = 0
    n = len(height)

    #find the max area between two indices where height is determined by the shorter of the two locations
    #start with left and right pointers at opposite ends
    #check area
    #keep moving in the lower of the two heights since that is the only way to improve the area
    #if height is equal does not matter which you move
    #repeat until left==right
    left = 0
    right = n-1
    while left!=right:
        h1 = height[left]
        h2 = height[right]
        width = right - left
        current_area = min(h1, h2) * width
        max_area = max(max_area, current_area)
        if h1<=h2:
            left+=1
        else:
            right-=1

    return max_area
