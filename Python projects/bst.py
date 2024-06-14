class bst:
    def __init__(self,data=None):
        """
        Initializes the binary search tree (bst) node.

        Parameters:
        data: The value of the node. Default is None."""
        self.left = None  # Initialize left child
        self.right = None  # Initialize right child
        self.parent = None  # Initialize parent node
        self.data = data  # Set node value


    def insert(self,data):
        """
        Inserts a new node into the binary search tree.

        Parameters:
        data: The value to be inserted into the tree."""
        #if user didn't initalize the root node earlier
        if self.data== None :
            self.data=data
            return self
        else:
            #this pointer will traverse the tree untill its position
            bst_traverse =self
            while True :
                if data <=bst_traverse.data :
                    #if left child is None then its the place for putting the new node
                    if bst_traverse.left ==None:
                        bst_traverse.left=bst(data)
                        bst_traverse.left.parent= bst_traverse
                        #traversing the bst is finished by this condition
                        break
                    else :
                        #go left
                        bst_traverse = bst_traverse.left
                elif data > bst_traverse.data and bst_traverse.right==None:
                    #inserts a new node at right child
                    bst_traverse.right=bst(data)
                    bst_traverse.right.parent= bst_traverse
                    break
                else:
                    #go right
                    bst_traverse = bst_traverse.right

    def search(self,data):
        """
        Searches for a node with the specified data in the binary search tree.

        Parameters:
        data: The value to search for in the tree.

        Returns:
        A list where the first element is a boolean indicating whether the data was found,
        and the second element is the node containing the data if it was found, or None otherwise.
        """
        bst_traverse = self
        while True :
            if data ==bst_traverse.data:
                return [True,bst_traverse]

            elif data <bst_traverse.data:
                # If the current node has no left child and the search data is less than the current node's data,
                # the search data is not in the tree, so return False and None
                if bst_traverse.left==None:
                    return [False,None]
                else:
                    #keep traversing
                    bst_traverse =bst_traverse.left
            else:
                #checks if there is a right child
                if bst_traverse.right==None:
                    return [False,None]
                else:
                    bst_traverse=bst_traverse.right

    def replace(self,dest_data,src_data):
        """
        Replaces a node with specified data (dest_data) in the binary search tree with a new node with different data (src_data).

        Parameters:
        dest_data: The data of the node to be replaced.
        src_data: The data for the new node that will replace the old node.

        Returns:
        True if the replacement was successful, False otherwise.
        """
        logic,temp_node= self.search(dest_data)
        if logic ==True :
            if src_data!=temp_node.data:
                temp_node.del_node(temp_node.data)
                self.insert(src_data)
            return True

        return False



    def min(self):
        """This function returns minimum data or leftmost node's data """
        bst_traverse=self
        while bst_traverse.left !=None :
            bst_traverse=bst_traverse.left
        return bst_traverse.data

    def max(self):
        """This function returns maximum data or rightmost node's data"""
        bst_traverse = self
        while bst_traverse.right !=None :
            bst_traverse=bst_traverse.right
        return bst_traverse.data


    def is_left_child(self):
        """checks if current node is a left child of the parent node"""
        return self.parent!=None and self.data<=self.parent.data

    def is_right_child(self):
        """checks if current node is a right child of the parent node"""
        return self.parent!=None and self.data>self.parent.data

    def update_parent_nodes(self,dest_node):
        """
        Updates the parent node's left or right child according to the destination node.

        If the current node is the left child of its parent, the parent's left child is updated to be the destination node.
        If the current node is the right child of its parent, the parent's right child is updated to be the destination node.

        This method is primarily used in the `del_node` function to maintain the binary search tree properties after a node deletion.

        Parameters:
        dest_node: The node to replace the current node in the parent's children.
        """
        if  self.parent != None :
            if self.is_left_child() :
                self.parent.left=dest_node
            else:
                self.parent.right=dest_node

    def del_node(self, data):
        """
        Deletes a node with the specified data from the binary search tree.

        Parameters:
        data: The data of the node to be deleted.

        Returns:
        True if the deletion was successful, False otherwise.
        """
        bst_traverse = self  # Start at the root

        # Search for the node to be deleted
        while True:
            if data == bst_traverse.data:
                break
            elif data < bst_traverse.data:
                if bst_traverse.left is not None:
                    bst_traverse = bst_traverse.left
                else:
                    return False  # Node not found
            else:
                if bst_traverse.right is not None:
                    bst_traverse = bst_traverse.right
                else:
                    return False  # Node not found

        # If the node to be deleted has no children
        if bst_traverse.left is None and bst_traverse.right is None:
            bst_traverse.update_parent_nodes(None)
        # If the node to be deleted has only a right child
        elif bst_traverse.left is None:
            bst_traverse.right.parent = bst_traverse.parent  # Update child's parent reference
            bst_traverse.update_parent_nodes(bst_traverse.right)
        # If the node to be deleted has only a left child
        elif bst_traverse.right is None:
            bst_traverse.left.parent = bst_traverse.parent  # Update child's parent reference
            bst_traverse.update_parent_nodes(bst_traverse.left)
        # If the node to be deleted has two children
        else:
            # Find the minimum data in the right subtree
            min_data = bst_traverse.right.min()
            # Delete the node with the minimum data in the right subtree
            bst_traverse.right.del_node(min_data)
            # Replace the data of the node to be deleted with the minimum data
            bst_traverse.data = min_data

        return True  # Node deletion successful

    def del_bst(self,data = None):
        """
        Deletes a subtree from the binary search tree. If no data is provided, the entire tree is deleted.

        Parameters:
        data: The data of the root node of the subtree to be deleted. If None, the entire tree is deleted.
        """
        #abstracted from user
        def del_all(self):
            if self.left is not None:
                del_all(self.left)
            if self.right is not None:
                del_all(self.right)
            self.update_parent_nodes(None)
            self.parent=None
        #by default it deltes the root node (all the bst)
        if data==None:
            bst_traverse= self
        #look for documentation of @search to understant why its values returned like that
        else :
            logic,bst_traverse =self.search(data)

        if bst_traverse :

            del_all(bst_traverse)
            #this function updates the parent's link related to that child
            #so if the node is left child then the parent left child link is updated to None
            #so it can be collected by the garbage collector (C is more fun though)
            bst_traverse.update_parent_nodes(None)
            bst_traverse.parent=None
            bst_traverse.data=None


    def parent(self,data):
        """Returns parent of data if it exists in the bst"""
        logic,temp_node=self.search(data)

        if logic==True and temp_node !=None :
            return temp_node.parent.data
        else:
            return None

    def predecessor(self,data):
        """in a sorted bst this function returns the previous element
            in an inorder display of the elements
            ex : 1 ,2 ,3 ,4 ,5
            predecessor(3) = 2
        """
        logic,temp_node = self.search(data)
        #node indeed exists
        if logic==True:
            #hold the data in a temporary variable
            temp_data = temp_node.data
            #the predecessor of an element is the maximum element in the left subtree
            if  temp_node.left!=None:
                return temp_node.left.max()

            #if the current node is left child this creates a problem we need to keep visiting parents
            #till the temp_data is bigger than the node so this becomes the predecessor
            #watch @mycodeschool videos he is a legend
            elif temp_node.is_left_child():
            # while value is bigger visit parents
            #if the loop doesn't start then it must be minimum data
                while temp_node!=None:
                    if  temp_data > temp_node.data:
                        return temp_node.data

                    temp_node= temp_node.parent
            #this occurs when user passes minimum data so no predecessor in the bst
                else:
                    return None
            #if the node is a right child then you are lucky its just the data of the parent node
            return temp_node.parent.data
        #if node doesn't exists in the first place just return None
        return None

    def successor(self,data):
        """in a sorted bst this function returns the next element
            in an inorder display of the elements
            ex : 1 ,2 ,3 ,4 ,5
            successor(3) = 4
        """
        #search for the node first
        logic,temp_node = self.search(data)
        if logic==True:
            #hold the data in a temporary variable
            temp_data = temp_node.data

            if  temp_node.right!=None:
                #you are lucky if there is a right child for that node since
                #the successor is minimum of right subtree
                return temp_node.right.min()

            #now you aren't lucky
            elif temp_node.is_right_child():
            # while value is smaller visit parents
            #if the loop doesn't start then it must be Maximum data
                while temp_node!=None:
                    if  temp_data < temp_node.data:
                        return temp_node.data

                    temp_node= temp_node.parent
                else:
                    return None

            else:
                #if its a left child with no right subtree then parent is the successor
                return temp_node.parent.data
        return None

    def inorder(self):
        """This function performs inorder traversal of the bst"""
        #first check if left child is not None to prevent errors
        if self.left != None:
            #go left
            self.left.inorder()
        #prints of the node
        print(self.data)
        #again check if left child isn't None
        if self.right != None:
            #go right
            self.right.inorder()

    def postorder(self):
        """Children are vested first then the data is printed"""
        if self.left != None:
            self.left.postorder()
        if self.right  != None:
            self.right.postorder()
        print(self.data)


    def reverse_order(self):
        """Displays data on the bst in decending order"""
        if self.right != None:
            self.right.reverse_order()
        print(self.data)
        if self.left != None:
            self.left.reverse_order()


    def choose_order(self,order=None):
        """
        Chooses the order of traversal for the binary tree.
        Parameters:
        order (str): The order of traversal. Options are:
        'in' for in-order traversal,
        'rev' for reverse order traversal,
        'post' for post-order traversal.
        By default, it performs in-order traversal.
        """
        if order=='in' or order==None:
            self.inorder()
        elif order=='rev':
            self.reverse_order()
        elif order =='post' :
            self.postorder()
        else :
            self.inorder()

    def height(self,data=None):
        """
        Recursively calculates the height of a tree.

        Parameters:
        node: The root node of the tree.
        """
        #watch @mycodeschool if the following piece of code is confusing
        def get_height(self):
            # Initialize the heights of the left and right subtrees
            left_height = -1
            right_height = -1

            if self.left!=None:
                left_height=get_height(self.left)

            if self.right !=None:
                right_height =get_height(self.right)
            # The height of the tree is the maximum height of the subtrees plus 1
            return max([left_height,right_height])+1

        if data :
            #so user passed data so we calculate height for the subtree
            logic,temp_node =self.search(data)
            if logic:
                return get_height(temp_node)
        #return height of whole bst by default
        else :
            return get_height(self)

    def depth(self,data=None):
        """
        Returns the depth of a node in the binary search tree.
        If no data is provided, the depth of the root node is returned (zero ofcourse)

        Parameters:
        data: The data of the node. If None, the depth of the root node is returned.
        """
        if data:
            bst_traverse = self
            counter = 0
            while True :
                #while traversing (searching for the node the counter increments)
                #for each edge that it passes
                if data ==bst_traverse.data:
                    return counter

                elif data<bst_traverse.data:
                    #node doesn't exist
                    if bst_traverse.left !=None:
                        bst_traverse=bst_traverse.left
                    else :
                        return -1
                else :
                    if bst_traverse.right !=None:
                        bst_traverse = bst_traverse.right
                    else :
                        return-1

                counter+=1

            return counter
        else:
            return 0

    def count(self,data =None):
        """
        Returns the number of nodes in a subtree of the binary search tree.
        If no data is provided, the number of nodes in the entire tree is returned.

        Parameters:
        data: The data of the root node of the subtree. If None, the number of nodes in the entire tree is returned.
        """
        counter=0
        if data==None:
            bst_traverse= self
        else :
            logic,bst_traverse =self.search(data)

        if bst_traverse!=None:
            if bst_traverse.left!=None:
               counter += bst_traverse.left.count()
            if bst_traverse.right!=None:
                counter += bst_traverse.right.count()

            return counter+1




