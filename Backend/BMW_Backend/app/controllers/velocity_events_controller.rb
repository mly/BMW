class VelocityEventsController < ApplicationController
  # GET /velocity_events
  # GET /velocity_events.xml
  def index
    @velocity_events = VelocityEvent.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @velocity_events }
    end
  end

  # GET /velocity_events/1
  # GET /velocity_events/1.xml
  def show
    @velocity_event = VelocityEvent.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @velocity_event }
    end
  end

  # GET /velocity_events/new
  # GET /velocity_events/new.xml
  def new
    @velocity_event = VelocityEvent.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @velocity_event }
    end
  end

  # GET /velocity_events/1/edit
  def edit
    @velocity_event = VelocityEvent.find(params[:id])
  end

  # POST /velocity_events
  # POST /velocity_events.xml
  def create
    @velocity_event = VelocityEvent.new(params[:velocity_event])

    respond_to do |format|
      if @velocity_event.save
        format.html { redirect_to(@velocity_event, :notice => 'Velocity event was successfully created.') }
        format.xml  { render :xml => @velocity_event, :status => :created, :location => @velocity_event }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @velocity_event.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /velocity_events/1
  # PUT /velocity_events/1.xml
  def update
    @velocity_event = VelocityEvent.find(params[:id])

    respond_to do |format|
      if @velocity_event.update_attributes(params[:velocity_event])
        format.html { redirect_to(@velocity_event, :notice => 'Velocity event was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @velocity_event.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /velocity_events/1
  # DELETE /velocity_events/1.xml
  def destroy
    @velocity_event = VelocityEvent.find(params[:id])
    @velocity_event.destroy

    respond_to do |format|
      format.html { redirect_to(velocity_events_url) }
      format.xml  { head :ok }
    end
  end
end
