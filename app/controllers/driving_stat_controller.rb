class DrivingStatController < ApplicationController
      def list
          @stats = DrivingStat.find(:all)
      end

      def show
          @stat = DrivingStat.find(params[:id])
      end

      def index
      	  create
      end   

      def new
          @stat = DrivingProfile.new
      end

      def create
      	  # Todo: decode from a JSON string in the URL
	
	  @stat = DrivingStat.new(params[:driving_stat])
	  
	  @stat.iphone_timestamp = params[:iphone_timestamp]
	  @stat.velocity = params[:velocity]
	  @stat.acceleration = params[:acceleration]
	  @stat.latitude = params[:latitude]
	  @stat.longitude = params[:longitude]
	  @stat.num_redlights = params[:num_redlights]
	  
	  if @stat.save
             redirect_to :action => 'list'
          end
      end

      def delete
      	  DrivingStat.find(params[:id]).destroy
          redirect_to :action => 'list'
      end
end
