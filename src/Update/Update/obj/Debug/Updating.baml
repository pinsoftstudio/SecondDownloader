   M S B A M L   `   `   `  ����A  =Update, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:UpdateUpdate  5          Update.Updating   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      U QWpfAnimatedGif, Version=2.0.0.0, Culture=neutral, PublicKeyToken=9e7cd3b544a090dc,gif"http://wpfanimatedgif.codeplex.com  5       localclr-namespace:Update  5        N� Title$  Updating��5
       � 	Resources 5       �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers :� RoutedEvent	 �� TargetProperty	
 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse  btn��%Y  &	        &	 %    �� 5   
   " ��6   .�5      ��  � ��
 �����6+   �� 5       � �� �#2983cc6+   �� 5       �@�Cursor$
 Hand��6'   �� 5       � �� 5      �� 5      " ��6&   .R�5      �� #��z��6!   $ 6��6K   ._�5      �� $��Center=�6/   $��Center=�6L   5      5      5       5      :� 5      $ Button.MouseEnter��6   [�5      �� 5      .��5      �� .��5   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #4f9dddX�5   %   $ 0:0:0.1D�62   $ HoldEnd=�6E   6^   5$      5%      5'      :� 5(      $ Button.MouseLeave��6   [�5)      �� 5*      .��5+      �� .��5,   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #2983ccX�5-   %   $ 0:0:0.1D�62   6G   5/      50      52      :� 53      $ Button.Click��6   [�54      �� 55      .��56      �� .��57   "   W� $	 (Button.Opacity)�58      $ 1X�59      $	 0.8X�6   $ 0:0:0.2D�6    . 6,   5:      5;      5=      5?      �� 5@   
   " ��6   .�5A      ��  � �� �#0006+   �� 5B       � �� �#ddd6+   �� 5C       �@�Cursor$
 Hand��6'   �� 5D       � �� 5E      �� 5F      " ��6&   .R�5G      �� #��z��6!   $ 6��6K   ._�5H      �� $��Center=�6/   $��Center=�6L   5I      5J      5L       5M      :� 5N      $ Button.MouseEnter��6   [�5O      �� 5P      .��5Q      �� .��5R   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #e7e7e7X�5S   %   $ 0:0:0.1D�62   $ HoldEnd=�6E   6^   5X      5Y      5[      :� 5\      $ Button.MouseLeave��6   [�5]      �� 5^      .��5_      �� .��5`   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $

 #dddX�5a   %   $ 0:0:0.1D�6/   6D   5c      5d      5f      :� 5g      $ Button.Click��6   [�5h      �� 5i      .��5j      �� .��5k   "   W� $	 (Button.Opacity)�5l      $ 1X�5m      $	 0.7X�6   $ 0:0:0.2D�6    . 6,   5n      5o      5q      5s      5t      .��5u      � 
�������.+�5v   
   �� $
��Left=�6   $��20��6+   $��10,1,0,0q�67   $	��Top=�6I   $��22��6a   $��	/icon.ico��6l    J� OpacityMask 5w      �� 5x       �� ImageSource$ /update.png��6    j� Stretch$ Uniform=�67   5z      �� 5{   
   $��在线升级��6   $
��Left=�6   $��	40,-4,0,0q�6:   $	��Top=�6M   $	��177��6e   $��15(�6q   $��34��6   �� 5|   
   $��正在更新
��6   $
��Left=�6$   $��
178,91,0,0q�6?   $	��Top=�6S   $	��286��6k   $��20(�6w   $��34��6�   ��5}      �� 5~      5�      �� 5�   
   "  WpfAnimatedGif.ImageBehavior   AnimatedSource$ /loading.gif��6   $��77,34,92,130q�6@   �� 5�   
   -   5         ��Name$ 
labVersion��5�      $��最新版本��6$   $��Center=�63   $��	0,398,0,0q�6P   $	��Top=�6c   $	��232��6{   $��20(�6�   $��Center=�6�   ��5�      �� 5�      5�      �� 5�   
   -   5        $ labelStatus��5�      $��正在准备下载：��6%   $��Center=�67   $��	0,525,0,0q�6T   $	��Top=�6g   $	��430��6   $��15(�6�   � 5�   
   -   5         �Name$ progressbar��5�      $��19��6+   $��
10,0,10,10q�67   $��Bottom=�6K   ���	#FF2983CC���#eee��6�   Z� �� 5�   
   $��27��6   $��6,0,6,6q�6    $��Bottom=�61   
�������$��4��6[    �� RadiusX$ 9��6o    �� RadiusY$	 8.7��6{   5�      5�      