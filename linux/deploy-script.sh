echo 

APP_DIR="/home/ubuntu/group_11/backend"
APP_NAME="app.js"
BRANCH="backend-linux"

echo "--------------------------------"
echo "git pull..."
echo "--------------------------------"
cd $APP_DIR
git fetch origin
git checkout $BRANCH
git pull origin $BRANCH
chmod +x /home/ubuntu/group_11/linux/deploy-backend.sh
npm install

echo "--------------------------------"
echo "update & upgrade"
echo "--------------------------------"
sudo apt update -y
sudo apt upgrade -y

echo "--------------------------------"
echo "pm2 reload"
echo "--------------------------------"
pm2 restart group11-backend

echo "--------------------------------"
echo "nginx restart..."
echo "--------------------------------"
sudo cp /home/ubuntu/group_11/linux/backend /etc/nginx/sites-available
sudo systemctl reload nginx

echo "--------------------------------"
echo "deploy ready"
echo "--------------------------------"
