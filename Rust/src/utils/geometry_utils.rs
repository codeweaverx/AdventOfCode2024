use std::ops;
//use std::fmt::Display;
use std::fmt::Debug;


#[derive(Debug)]
#[derive(Copy)]
#[derive(Clone)]
#[derive(Hash)]
pub struct V2<T> {
    pub x: T,
    pub y: T
}


impl<T> V2<T> {
    fn new(x:T, y:T) -> V2<T> {
        V2{x,y}
    }

}

impl<T> ops::Add<V2<T>> for V2<T> 
  where T : ops::Add<Output = T>
{
    type Output = V2<T>;

    fn add(self, _rhs: V2<T>) -> V2<T> {
        V2{x : self.x+_rhs.x, y : self.y+_rhs.y}
    }
}


impl<T> ops::Sub<V2<T>> for V2<T> 
  where T : ops::Sub<Output = T>
{
    type Output = V2<T>;

    fn sub(self, _rhs: V2<T>) -> V2<T> {
        V2{x : self.x-_rhs.x, y : self.y-_rhs.y}
    }
}

impl<T> ops::Mul<T> for V2<T>
  where T : ops::Mul<Output = T> + Clone
{
    type Output = V2<T>;

    fn mul(self, s: T) -> V2<T> {
        V2{x : self.x * s.clone(), y : self.y * s}
    }
}


impl<T> PartialEq for V2<T>
  where T : PartialEq
{
    fn eq(&self, _rhs: &V2<T>) -> bool {
        self.x == _rhs.x && self.y == _rhs.y
    }
}

impl<T> Eq for V2<T>
  where T : PartialEq
{
}

